#include "Level.h"
#include <boost/lexical_cast.hpp>
#include <boost/format.hpp>
#include <boost/foreach.hpp>
#include <fstream>
#include <ctime>

using namespace boost;

const float Level::MINIMAL_ATTACK_FACTOR = 0.75;
const float Level::MAXIMAL_ATTACK_FACTOR = 1.25;
const regex Level::LEVEL_FILE_LINE_PATTERN(
	"(0|[1-9]\\d*) (tree|mountain|castle) (0|[1-9]\\d*) (0|[1-9]\\d*)"
);

Level::Level(const std::string& filename) :
	last_id(0)
{
	std::srand(std::time(NULL));

	int minimal_x = 0;
	int minimal_y = 0;
	int maximal_x = 0;
	int maximal_y = 0;

	std::ifstream in(filename.c_str());
	while (in) {
		std::string line;
		std::getline(in, line);
		if (line.empty()) {
			continue;
		}

		smatch matches;
		if (regex_match(line, matches, LEVEL_FILE_LINE_PATTERN)) {
			std::string entity_type = matches[2];
			if (
				entity_type == "tree"
				|| entity_type == "mountain"
				|| entity_type == "castle"
			) {
				last_id = lexical_cast<size_t>(matches[1]);

				Position position(
					lexical_cast<int>(matches[3]),
					lexical_cast<int>(matches[4])
				);

				held_positions.push_back(position);
				if (entity_type == "castle") {
					castles[last_id] = CastleSmartPointer(
						new Castle(INVALID_ID)
					);
					castles[last_id]->position = position;
				}

				if (position.x < minimal_x) {
					minimal_x = position.x;
				} else if (position.x > maximal_x) {
					maximal_x = position.x;
				}
				if (position.y < minimal_y) {
					minimal_y = position.y;
				} else if (position.y > maximal_y) {
					maximal_y = position.y;
				}
			} else {
				std::cerr
					<< (format(
						"Warning! Invalid entity type \"%s\" in level file.\n"
					) % entity_type).str();
				continue;
			}
		} else {
			std::cerr
				<< (format("Warning! Invalid line \"%s\" in level file.\n")
					% line).str();
		}
	}

	for (int x = minimal_x; x <= maximal_x; ++x) {
		for (int y = minimal_y; y <= maximal_y; ++y) {
			Position position(x, y);
			if (!isPositionHeld(position)) {
				not_held_positions.push_back(position);
			}
		}
	}
}

std::string Level::toString(size_t player_id) {
	lock_guard<boost::mutex> guard(mutex);

	std::string result;
	std::map<size_t, CastleSmartPointer>::const_iterator i = castles.begin();
	for (; i != castles.end(); ++i) {
		size_t castle_state =
			i->second->owner == INVALID_ID
				? 0
				: i->second->owner == player_id
					? 1
					: 2;
		result +=
			(format("c:%u:%u:%u;")
				% i->first
				% i->second->health
				% castle_state).str();
	}
	std::map<size_t, PlayerSmartPointer>::const_iterator j = players.begin();
	for (; j != players.end(); ++j) {
		result +=
			(format("p:%u:%u:%i:%i;")
				% j->first
				% j->second->health
				% j->second->position.x
				% j->second->position.y).str();
	}
	result = result.substr(0, result.length() - 1);

	return result;
}

size_t Level::addPlayer(void) {
	lock_guard<boost::mutex> guard(mutex);

	last_id++;

	size_t default_health = getDefaultHealth();
	players[last_id] = PlayerSmartPointer(new Player(default_health));

	players[last_id]->position = getRandomUnholdPosition();
	holdPosition(players[last_id]->position);

	return last_id;
}

bool Level::movePlayer(size_t player_id, Direction direction) {
	lock_guard<boost::mutex> guard(mutex);

	if (!players.count(player_id)) {
		throw std::runtime_error("invalid player id");
	}

	Position position = players[player_id]->position;
	switch (direction) {
		case DIRECTION_UP:
			position.y--;
			break;
		case DIRECTION_RIGHT:
			position.x++;
			break;
		case DIRECTION_DOWN:
			position.y++;
			break;
		case DIRECTION_LEFT:
			position.x--;
			break;
	}

	bool can_move = !isPositionHeld(position);
	if (can_move) {
		holdPosition(position);
		unholdPosition(players[player_id]->position);

		players[player_id]->position = position;
	} else {
		size_t attack_value = getAttackValue(players[player_id]->health);
		size_t enemy_id = getPlayerByPosition(position);
		if (enemy_id != INVALID_ID) {
			decreasePlayerHealth(enemy_id, attack_value);
		} else {
			size_t enemy_id = getCastleByPosition(position);
			if (
				enemy_id != INVALID_ID
				&& castles[enemy_id]->owner != player_id
			) {
				decreaseCastleHealth(enemy_id, attack_value, player_id);
			}
		}
	}

	return can_move;
}

void Level::updatePlayerTimestamp(size_t player_id) {
	lock_guard<boost::mutex> guard(mutex);

	if (!players.count(player_id)) {
		throw std::runtime_error("invalid player id");
	}

	players.at(player_id)->timestamp = std::time(NULL);
}

void Level::removeLostPlayers(void) {
	lock_guard<boost::mutex> guard(mutex);

	std::map<size_t, PlayerSmartPointer>::iterator i = players.begin();
	time_t current_timestamp = std::time(NULL);
	while (i != players.end()) {
		if (
			current_timestamp - i->second->timestamp >= MAXIMAL_PLAYER_TIMEOUT
		) {
			unholdPosition(i->second->position);
			players.erase(i++);
		} else {
			++i;
		}
	}
}

bool Level::isPositionHeld(const Position& position) const {
	return
		std::find(held_positions.begin(), held_positions.end(), position)
		!= held_positions.end();
}

void Level::holdPosition(const Position& position) {
	if (!isPositionHeld(position)) {
		held_positions.push_back(position);

		not_held_positions.erase(
			std::remove(
				not_held_positions.begin(),
				not_held_positions.end(),
				position
			),
			not_held_positions.end()
		);
	}
}

void Level::unholdPosition(const Position& position) {
	if (isPositionHeld(position)) {
		held_positions.erase(
			std::remove(
				held_positions.begin(),
				held_positions.end(),
				position
			),
			held_positions.end()
		);

		not_held_positions.push_back(position);
	}
}

size_t Level::getAttackValue(size_t base_value) const {
	float attack_factor =
		static_cast<float>(std::rand())
		/ RAND_MAX
		* (MAXIMAL_ATTACK_FACTOR - MINIMAL_ATTACK_FACTOR)
		+ MINIMAL_ATTACK_FACTOR;
	return static_cast<size_t>(std::floor(attack_factor * base_value + 0.5f));
}

size_t Level::getCastleByPosition(const Position& position) const {
	std::map<size_t, CastleSmartPointer>::const_iterator i = castles.begin();
	for (; i != castles.end(); ++i) {
		if (i->second->position == position) {
			return i->first;
		}
	}

	return INVALID_ID;
}

void Level::decreaseCastleHealth(
	size_t castle_id,
	size_t value,
	size_t player_id
) {
	if (castles[castle_id]->health > value) {
		castles[castle_id]->health -= value;
	} else {
		resetCastle(castle_id, player_id);
	}
}

void Level::resetCastle(size_t castle_id, size_t player_id) {
	castles[castle_id]->health = Castle::DEFAULT_HEALTH;
	castles[castle_id]->owner = player_id;
}

Position Level::getRandomUnholdPosition(void) const {
	if (not_held_positions.empty()) {
		throw std::runtime_error("all positions're held");
	}

	return not_held_positions[std::rand() % not_held_positions.size()];
}

size_t Level::getDefaultHealth(void) const {
	if (!players.empty()) {
		size_t health_sum = 0;
		std::map<size_t, PlayerSmartPointer>::const_iterator i =
			players.begin();
		for (; i != players.end(); ++i) {
			health_sum += i->second->health;
		}

		return health_sum / players.size();
	} else {
		return Player::DEFAULT_HEALTH;
	}
}

size_t Level::getPlayerByPosition(const Position& position) const {
	std::map<size_t, PlayerSmartPointer>::const_iterator i = players.begin();
	for (; i != players.end(); ++i) {
		if (i->second->position == position) {
			return i->first;
		}
	}

	return INVALID_ID;
}

void Level::decreasePlayerHealth(size_t player_id, size_t value) {
	if (players[player_id]->health > value) {
		players[player_id]->health -= value;
	} else {
		resetPlayer(player_id);
	}
}

void Level::resetPlayer(size_t player_id) {
	unholdPosition(players[player_id]->position);
	players[player_id]->position = getRandomUnholdPosition();
	holdPosition(players[player_id]->position);

	players[player_id]->health = getDefaultHealth();
}
