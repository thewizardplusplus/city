#include "Castle.h"
#include <ctime>

Castle::Castle(size_t owner) :
	timestamp(std::time(NULL)),
	health(START_HEALTH),
	owner(owner)
{}
