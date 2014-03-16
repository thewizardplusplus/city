#ifndef LEVEL_H
#define LEVEL_H

#include "Player.h"
#include <boost/regex.hpp>
#include <list>
#include <vector>
#include <map>

enum Direction {
	DIRECTION_UP,
	DIRECTION_RIGHT,
	DIRECTION_DOWN,
	DIRECTION_LEFT
};

class Level {
public:
	Level(const std::string& filename);
	operator std::string(void) const;
	size_t addPlayer(void);
	void movePlayer(size_t player_id, Direction direction);
	void updatePlayerTimestamp(size_t player_id);
	void removeLostPlayers(void);

private:
	static const boost::regex LEVEL_FILE_LINE_PATTERN;
	static const time_t MAXIMAL_PLAYER_TIMEOUT = 12;

	std::list<Position> held_positions;
	std::vector<Position> not_held_positions;
	size_t last_player_id;
	std::map<size_t, PlayerSmartPointer> players;

	bool isPositionHeld(const Position& position) const;
};
#endif
