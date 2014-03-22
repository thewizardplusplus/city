#include "Level.h"
#include "SpriteFactory.h"
#include <boost/lexical_cast.hpp>
#include <boost/format.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/foreach.hpp>
#include <boost/algorithm/string.hpp>
#include <fstream>
#include <iostream>

using namespace boost;
using namespace boost::assign;
using namespace boost::algorithm;

const boost::regex Level::LEVEL_FILE_LINE_PATTERN(
	"(0|[1-9]\\d*) (tree|mountain|castle) (0|[1-9]\\d*) (0|[1-9]\\d*)"
);
const sf::Color Level::BACKGROUND_COLOR(0x22, 0x8b, 0x22);
const float Level::GRID_THICKNESS = 2.0f;
const sf::Color Level::GRID_COLOR(128, 128, 128);

Level::Level(
	size_t player_id,
	const sf::Vector2i& visual_size,
	const std::string& filename
) :
	player_id(player_id),
	visual_size(visual_size)
{
	sprites[SPRITE_TREE] = SpriteFactory::getInstance().loadSprite("tree.png");
	sprites[SPRITE_MOUNTAIN] = SpriteFactory::getInstance().loadSprite(
		"mountain.png"
	);
	sprites[SPRITE_GREY_CASTLE] = SpriteFactory::getInstance().loadSprite(
		"grey_castle.png"
	);
	sprites[SPRITE_GREEN_CASTLE] = SpriteFactory::getInstance().loadSprite(
		"green_castle.png"
	);
	sprites[SPRITE_RED_CASTLE] = SpriteFactory::getInstance().loadSprite(
		"red_castle.png"
	);
	sprites[SPRITE_GREEN_PLAYER] = SpriteFactory::getInstance().loadSprite(
		"green_player.png"
	);
	sprites[SPRITE_RED_PLAYER] = SpriteFactory::getInstance().loadSprite(
		"red_player.png"
	);
	BOOST_FOREACH(const SpriteGroup::value_type& sprite, sprites) {
		sprite.second->setSize(Entity::SIZE, Entity::SIZE);
	}

	label.SetSize(Entity::SIZE / 4.0f);
	label.SetStyle(sf::String::Bold);
	label.SetColor(sf::Color::White);

	std::ifstream in(filename.c_str());
	while (in) {
		std::string line;
		std::getline(in, line);
		if (line.empty()) {
			continue;
		}

		boost::smatch matches;
		if (boost::regex_match(line, matches, LEVEL_FILE_LINE_PATTERN)) {
			std::string entity_type = matches[2];
			size_t id = boost::lexical_cast<size_t>(matches[1]);
			sf::Vector2i position(
				boost::lexical_cast<size_t>(matches[3]),
				boost::lexical_cast<size_t>(matches[4])
			);
			if (entity_type == "tree") {
				EntitySmartPointer tree(new Entity(id));
				tree->setPosition(position);

				trees.push_back(tree);
			} else if (entity_type == "mountain") {
				EntitySmartPointer mountain(new Entity(id));
				mountain->setPosition(position);

				mountains.push_back(mountain);
			} else if (entity_type == "castle") {
				castles[id] = VariableEntitySmartPointer(
					new VariableEntity(id, 3)
				);
				castles[id]->setPosition(position);
			} else {
				std::cerr
					<< (boost::format(
						"Warning! Invalid entity type \"%s\" in level file.\n"
					) % entity_type).str();
				continue;
			}
		} else {
			std::cerr
				<< (boost::format(
					"Warning! Invalid line \"%s\" in level file.\n"
				) % line).str();
		}
	}
}

size_t Level::getPlayerId(void) {
	lock_guard<boost::mutex> guard(mutex);
	return player_id;
}

void Level::update(const std::string& description) {
	lock_guard<boost::mutex> guard(mutex);

	players.clear();

	std::vector<std::string> entities_description;
	split(entities_description, description, is_any_of(";"));
	BOOST_FOREACH(std::string entity_description, entities_description) {
		std::vector<std::string> entity_data;
		split(entity_data, entity_description, is_any_of(":"));

		if (entity_data[0] == "c") {
			size_t castle_id = lexical_cast<size_t>(entity_data[1]);
			if (castles.count(castle_id)) {
				castles[castle_id]->setParameter(entity_data[2]);
				castles[castle_id]->setState(
					lexical_cast<size_t>(entity_data[3])
				);
			}
		} else if (entity_data[0] == "p") {
			size_t player_id = lexical_cast<size_t>(entity_data[1]);
			this->players[player_id] = VariableEntitySmartPointer(
				new VariableEntity(player_id, 2)
			);
			this->players[player_id]->setParameter(entity_data[2]);

			setEntityState(player_id, player_id != this->player_id);
			sf::Vector2i position(
				lexical_cast<int>(entity_data[3]),
				lexical_cast<int>(entity_data[4])
			);
			setPlayerPosition(player_id, position);
			if (player_id == this->player_id) {
				this->position = position - visual_size / 2;
			}
		}
	}
}

void Level::render(sf::RenderWindow& render) {
	lock_guard<boost::mutex> guard(mutex);

	sf::Vector2i render_size(render.GetWidth(), render.GetHeight());
	render.Draw(
		sf::Shape::Rectangle(
			0,
			0,
			render_size.x,
			render_size.y,
			BACKGROUND_COLOR
		)
	);

	BOOST_FOREACH(EntitySmartPointer static_entity, trees) {
		sf::Vector2i position = static_entity->getPosition() - this->position;
		sprites[SPRITE_TREE]->setPosition(
			Entity::SIZE * position.x,
			Entity::SIZE * position.y
		);
		sprites[SPRITE_TREE]->render(render);
	}

	BOOST_FOREACH(EntitySmartPointer static_entity, mountains) {
		sf::Vector2i position = static_entity->getPosition() - this->position;
		sprites[SPRITE_MOUNTAIN]->setPosition(
			Entity::SIZE * position.x,
			Entity::SIZE * position.y
		);
		sprites[SPRITE_MOUNTAIN]->render(render);
	}

	BOOST_FOREACH(VariableEntityGroup::value_type castle_wrapper, castles) {
		VariableEntitySmartPointer castle = castle_wrapper.second;
		sf::Vector2i position = castle->getPosition() - this->position;
		sf::Vector2f real_position(
			Entity::SIZE * position.x,
			Entity::SIZE * position.y
		);
		SpriteNames castle_sprite_name =
			castle->getState() == 0
				? SPRITE_GREY_CASTLE
				: castle->getState() == 1
					? SPRITE_GREEN_CASTLE
					: SPRITE_RED_CASTLE;
		sprites[castle_sprite_name]->setPosition(real_position);
		sprites[castle_sprite_name]->render(render);

		label.SetText(castle->getParameter());
		label.SetPosition(real_position);
		render.Draw(label);
	}

	BOOST_FOREACH(VariableEntityGroup::value_type player_wrapper, players) {
		VariableEntitySmartPointer player = player_wrapper.second;
		SpriteNames player_sprite_name =
			player->getState() == 0 ? SPRITE_GREEN_PLAYER : SPRITE_RED_PLAYER;
		sf::Vector2i position = player->getPosition() - this->position;
		sf::Vector2f real_position(
			Entity::SIZE * position.x,
			Entity::SIZE * position.y
		);
		sprites[player_sprite_name]->setPosition(real_position);
		sprites[player_sprite_name]->render(render);

		label.SetText(player->getParameter());
		label.SetPosition(real_position);
		render.Draw(label);
	}

	for (int y = 0; y < render_size.y; y += Entity::SIZE) {
		render.Draw(
			sf::Shape::Line(0, y, render_size.x, y, GRID_THICKNESS, GRID_COLOR)
		);
	}
	for (int x = 0; x < render_size.x; x += Entity::SIZE) {
		render.Draw(
			sf::Shape::Line(x, 0, x, render_size.y, GRID_THICKNESS, GRID_COLOR)
		);
	}
}

void Level::setEntityState(size_t id, size_t state) {
	if (players.count(id)) {
		players[id]->setState(state);
	} else {
		std::cerr
			<< (boost::format("Warning! Invalid entity id \"%u\".\n") % id)
				.str();
	}
}

void Level::setPlayerPosition(size_t id, const sf::Vector2i& position) {
	if (players.count(id)) {
		players[id]->setPosition(position);
	} else {
		std::cerr
			<< (boost::format("Warning! Invalid player id \"%u\".\n") % id)
				.str();
	}
}
