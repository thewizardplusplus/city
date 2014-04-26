#include "Castle.h"
#include <ctime>

Castle::Castle(size_t owner) :
	timestamp(std::time(NULL)),
	action_timestamp(std::time(NULL)),
	health(START_HEALTH),
	owner(owner)
{}

bool Castle::timeout(void) const {
	return std::time(NULL) - action_timestamp >= ACTION_TIMEOUT;
}

void Castle::update(void) {
	action_timestamp = std::time(NULL);
}
