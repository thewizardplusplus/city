#include "Position.h"

Position::Position(void) :
	x(0),
	y(0)
{}

Position::Position(int x, int y) :
	x(x),
	y(y)
{}

bool Position::operator==(const Position& sample) const {
	return x == sample.x && y == sample.y;
}
