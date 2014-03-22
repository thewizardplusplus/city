#include "Player.h"
#include <ctime>

Player::Player(void) :
	timestamp(std::time(NULL)),
	health(DEFAULT_HEALTH)
{}
