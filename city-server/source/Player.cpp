#include "Player.h"
#include <ctime>

Player::Player(void) :
	timestamp(std::time(NULL)),
	action_timestamp(std::time(NULL)),
	health(DEFAULT_HEALTH)
{}

bool Player::timeout(void) const {
	return std::time(NULL) - action_timestamp >= ACTION_TIMEOUT;
}

void Player::update(void) {
	action_timestamp = std::time(NULL);
}
