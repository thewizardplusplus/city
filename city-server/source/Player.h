#ifndef PLAYER_H
#define PLAYER_H

#include "Position.h"
#include <boost/shared_ptr.hpp>

class Player {
public:
	Position position;
	time_t timestamp;

	Player(void);
};

typedef boost::shared_ptr<Player> PlayerSmartPointer;
#endif
