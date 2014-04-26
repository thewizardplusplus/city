#ifndef SKELETON_H
#define SKELETON_H

#include "Position.h"
#include <boost/shared_ptr.hpp>

class Skeleton {
public:
	static const size_t DEFAULT_HEALTH = 50;
	static const time_t ACTION_TIMEOUT = 1;

	Position position;
	time_t action_timestamp;
	size_t health;

	Skeleton(size_t health);
	bool timeout(void) const;
	void update(void);
};

typedef boost::shared_ptr<Skeleton> SkeletonSmartPointer;
#endif
