#ifndef LEVEL_H
#define LEVEL_H

#include "Player.h"
#include <boost/regex.hpp>
#include <boost/thread/thread.hpp>
#include <boost/shared_ptr.hpp>
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
	static const size_t START_PLAYER_ID = 1;
	static const time_t MAXIMAL_PLAYER_TIMEOUT = 12;
	static const float MINIMAL_ATTACK_FACTOR;
	static const float MAXIMAL_ATTACK_FACTOR;

	Level(const std::string& filename);
	operator std::string(void);
	size_t addPlayer(void);
	bool movePlayer(size_t player_id, Direction direction);
	void updatePlayerTimestamp(size_t player_id);
	void removeLostPlayers(void);

private:
	static const boost::regex LEVEL_FILE_LINE_PATTERN;

	std::vector<Position> held_positions;
	std::vector<Position> not_held_positions;
	size_t last_player_id;
	std::map<size_t, PlayerSmartPointer> players;
	boost::mutex mutex;

	bool isPositionHeld(const Position& position) const;
	void holdPosition(const Position& position);
	void unholdPosition(const Position& position);
	size_t getPlayerByPosition(const Position& position) const;
	void decreasePlayerHealth(size_t player_id, size_t value);
	void resetPlayer(size_t player_id);
};

typedef boost::shared_ptr<Level> LevelSmartPointer;
#endif
