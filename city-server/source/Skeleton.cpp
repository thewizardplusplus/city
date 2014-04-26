#include "Skeleton.h"
#include <ctime>

Skeleton::Skeleton(size_t health) :
	action_timestamp(std::time(NULL)),
	health(health)
{}

bool Skeleton::timeout(void) const {
	return std::time(NULL) - action_timestamp >= ACTION_TIMEOUT;
}

void Skeleton::update(void) {
	action_timestamp = std::time(NULL);
}
