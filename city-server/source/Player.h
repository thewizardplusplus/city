#ifndef PLAYER_H
#define PLAYER_H

#include "Position.h"
#include <boost/shared_ptr.hpp>

class Player {
public:
	static const size_t DEFAULT_HEALTH = 25;
	static const time_t ACTION_TIMEOUT = 1;

	Position position;
	time_t timestamp;
	time_t action_timestamp;
	size_t health;

	Player(void);
	bool timeout(void) const;
	void update(void);
};

typedef boost::shared_ptr<Player> PlayerSmartPointer;
#endif
