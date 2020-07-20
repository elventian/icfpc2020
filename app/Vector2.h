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

	Vector2 capped() const;

	Vector2 getGravity() const;
	Vector2 getSomeNormalToGravity() const;
	
	static const Vector2 allDirections[8];
};

class Vector2F
{
public:
	Vector2F(double x, double y): m_x(x), m_y(y) {}
	Vector2F(const Vector2 v): m_x(v.x()), m_y(v.y()) {}
	double x() const { return m_x; }
	double y() const { return m_y; }
	double length() const;
	Vector2F operator*(double mult) const { return Vector2F(m_x * mult, m_y *mult); }
	Vector2F operator-(const Vector2F &other) const;
	Vector2F ofTheSameLengthAs(const Vector2F &other) const;
	Vector2 integerCapped() const;

private:
	double m_x;
	double m_y;
};

#endif // VECTOR2_H
