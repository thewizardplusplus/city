#ifndef POSITION_H
#define POSITION_H

class Position {
public:
	int x;
	int y;

	Position(void);
	Position(int x, int y);
	bool operator==(const Position& sample) const;
};
#endif
