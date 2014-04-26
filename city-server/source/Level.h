#ifndef LEVEL_H
#define LEVEL_H

#include "Castle.h"
#include "Player.h"
#include "Skeleton.h"
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
	static const time_t MAXIMAL_PLAYER_TIMEOUT = 12;
	static const time_t MAXIMAL_CASTLE_TIMEOUT = 5;
	static const time_t SKELETON_ADDING_TIMEOUT = 12;
	static const size_t MAXIMAL_SKELETONS_NUMBER = 7;
	static const float REAL_HEALHT_FACTOR;
	static const float REAL_ATTACK_FACTOR;
	static const float MINIMAL_ATTACK_FACTOR;
	static const float MAXIMAL_ATTACK_FACTOR;

	Level(const std::string& filename);
	std::string toString(size_t player_id);
	size_t addPlayer(void);
	bool movePlayer(size_t player_id, Direction direction);
	void updatePlayerTimestamp(size_t player_id);
	void removeLostPlayers(void);
	void updateCastles(void);
	void addSkeleton(void);
	void updateSkeletons(void);

private:
	static const boost::regex LEVEL_FILE_LINE_PATTERN;
	static const size_t INVALID_ID = static_cast<size_t>(-1);

	std::vector<Position> held_positions;
	std::vector<Position> not_held_positions;
	std::map<size_t, CastleSmartPointer> castles;
	size_t last_id;
	std::map<size_t, PlayerSmartPointer> players;
	time_t last_skeleton_adding_timestamp;
	std::map<size_t, SkeletonSmartPointer> skeletons;
	boost::mutex mutex;

	bool isPositionHeld(const Position& position) const;
	void holdPosition(const Position& position);
	void unholdPosition(const Position& position);
	size_t getAttackValue(size_t base_value) const;
	size_t getCastleByPosition(const Position& position) const;
	void decreaseCastleHealth(size_t castle_id, size_t value, size_t player_id);
	void resetCastle(size_t castle_id, size_t player_id);
	void unholdCastles(size_t player_id);
	Position getRandomUnholdPosition(void) const;
	size_t getDefaultHealth(size_t exception_id) const;
	size_t getPlayerByPosition(const Position& position) const;
	void decreasePlayerHealth(size_t player_id, size_t value);
	void resetPlayer(size_t player_id);
	size_t getSkeletonByPosition(const Position& position) const;
	void decreaseSkeletonHealth(size_t skeleton_id, size_t value);
	void killSkeleton(size_t skeleton_id);
	std::vector<Position> getNeighborhood(const Position& position) const;
	void skeletonRandomMove(size_t skeleton_id);
};

typedef boost::shared_ptr<Level> LevelSmartPointer;
#endif
