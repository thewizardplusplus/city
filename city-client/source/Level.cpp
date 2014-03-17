#include "Level.h"
#include "VariableEntity.h"
#include <boost/lexical_cast.hpp>
#include <boost/format.hpp>
#include <fstream>
#include <iostream>

using namespace boost;

const boost::regex Level::LEVEL_FILE_LINE_PATTERN(
	"(0|[1-9]\\d*) (tree|mountain|castle) (0|[1-9]\\d*) (0|[1-9]\\d*)"
);
const sf::Color Level::BACKGROUND_COLOR(0x22, 0x8b, 0x22);
const float Level::GRID_THICKNESS = 2.0f;
const sf::Color Level::GRID_COLOR(128, 128, 128);

Level::Level(size_t player_id, const std::string& filename) :
	player_id(player_id)
{
	StringGroup sprites_filenames;
	sprites_filenames.push_back("grey_castle.png");
	sprites_filenames.push_back("red_castle.png");
	sprites_filenames.push_back("green_castle.png");

	std::ifstream in(filename.c_str());
	while (in) {
		std::string line;
		std::getline(in, line);
		if (line.empty()) {
			continue;
		}

		boost::smatch matches;
		if (boost::regex_match(line, matches, LEVEL_FILE_LINE_PATTERN)) {
			Entity::Pointer entity;
			std::string entity_type = matches[2];
			size_t id = boost::lexical_cast<size_t>(matches[1]);
			if (entity_type == "tree") {
				entity.reset(new Entity(id, "tree.png"));
			} else if (entity_type == "mountain") {
				entity.reset(new Entity(id, "mountain.png"));
			} else if (entity_type == "castle") {
				VariableEntity::Pointer castle_entity(new VariableEntity(
					id,
					sprites_filenames
				));

				entity = castle_entity;
				castles[id] = castle_entity;
			} else {
				std::cerr
					<< (boost::format(
						"Warning! Invalid entity type \"%s\" in level file.\n"
					) % entity_type).str();
				continue;
			}

			entity->setPosition(
				boost::lexical_cast<size_t>(matches[3]),
				boost::lexical_cast<size_t>(matches[4])
			);
			entities.push_back(entity);
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

void Level::setPosition(const sf::Vector2i& position) {
	lock_guard<boost::mutex> guard(mutex);
	this->position = position;
}

void Level::setEntityState(size_t id, size_t state) {
	lock_guard<boost::mutex> guard(mutex);

	if (castles.count(id)) {
		castles[id]->setState(state);
	} else if (players.count(id)) {
		players[id]->setState(state);
	} else {
		std::cerr
			<< (boost::format("Warning! Invalid entity id \"%u\".\n") % id)
				.str();
	}
}

void Level::addPlayer(size_t id) {
	lock_guard<boost::mutex> guard(mutex);

	StringGroup sprites_filenames;
	sprites_filenames.push_back("green_player.png");
	sprites_filenames.push_back("red_player.png");

	players[id] = VariableEntity::Pointer(
		new VariableEntity(
			id,
			sprites_filenames
		)
	);
}

void Level::setPlayerPosition(size_t id, const sf::Vector2i& position) {
	lock_guard<boost::mutex> guard(mutex);

	if (players.count(id)) {
		players[id]->setPosition(position);
	} else {
		std::cerr
			<< (boost::format("Warning! Invalid player id \"%u\".\n") % id)
				.str();
	}
}

void Level::removeAllPlayer() {
	lock_guard<boost::mutex> guard(mutex);
	players.clear();
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

	EntityGroup::const_iterator i = entities.begin();
	for (; i != entities.end(); ++i) {
		Entity::Pointer entity = *i;
		entity->setPosition(entity->getPosition() - position);
		entity->render(render);
		entity->setPosition(entity->getPosition() + position);
	}

	VariableEntityGroup::const_iterator j = players.begin();
	for (; j != players.end(); ++i) {
		VariableEntity::Pointer player = j->second;
		player->setPosition(player->getPosition() - position);
		player->render(render);
		player->setPosition(player->getPosition() + position);
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
