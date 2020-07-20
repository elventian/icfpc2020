#ifndef VECTOR2_H
#define VECTOR2_H

#include <stdint.h>
#include "DiscrCoord2.h"

class ConsList;

class Vector2: public DiscrCoord2
{
public:
	Vector2() {}
	Vector2(const DiscrCoord2 &coord): DiscrCoord2(coord) {}
	Vector2(int64_t x, int64_t y): DiscrCoord2(x, y) {}
	Vector2(const ConsList *list);

	Vector2 getGravity() const;
};

#endif // VECTOR2_H
