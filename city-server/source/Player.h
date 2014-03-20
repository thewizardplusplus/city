#ifndef PLAYER_H
#define PLAYER_H

#include "Position.h"
#include <boost/shared_ptr.hpp>

class Player {
public:
	static const size_t DEFAULT_HEALTH = 25;

	Position position;
	time_t timestamp;
	size_t health;

	Player(size_t health);
};

typedef boost::shared_ptr<Player> PlayerSmartPointer;
#endif
