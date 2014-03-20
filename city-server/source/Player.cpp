#include "Player.h"
#include <ctime>

Player::Player(size_t health) :
	timestamp(std::time(NULL)),
	health(health)
{}
