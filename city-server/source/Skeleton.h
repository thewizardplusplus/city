#ifndef SKELETON_H
#define SKELETON_H

#include "Position.h"
#include <boost/shared_ptr.hpp>

class Skeleton {
public:
	static const size_t DEFAULT_HEALTH = 50;

	Position position;
	size_t health;

	Skeleton(size_t health);
};

typedef boost::shared_ptr<Skeleton> SkeletonSmartPointer;
#endif
