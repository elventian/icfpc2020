#include "Vector2.h"
#include "ConsList.h"
#include <math.h>

const Vector2 Vector2::allDirections[8] = 
{
	Vector2(1, 0),
	Vector2(1, 1),
	Vector2(0, 1),
	Vector2(0, -1),
	Vector2(-1, 0),
	Vector2(-1, 1),
	Vector2(-1, -1),
	Vector2(1, -1),
};

Vector2::Vector2(const ConsList *list)
{
	x() = (*list)[0]->intVal();
	y() = (*list)[1]->intVal();
}

Vector2 Vector2::capped() const
{
	int iX = x();
	if (iX > 1) { iX = 1; }
	else if (iX < -1) { iX = -1; }

	int iY = y();
	if (iY > 1) { iY = 1; }
	else if (iY < -1) { iY = -1; }

	return Vector2(iX, iY);
}

Vector2 Vector2::getGravity() const
{
	if (x() == 0 && y() == 0) { return Vector2(0, 0); }
	const int absX = abs(x());
	const int absY = abs(y());
	if (absX > absY) {
		return Vector2(-x() / absX, 0);
	}
	if (absX < absY) {
		return Vector2(0, -y() / absY);
	}
	return Vector2(-x() / absX, -y() / absY);
}

Vector2 Vector2::getSomeNormalToGravity() const
{
	if (x() == 0 && y() == 0) { return Vector2(0, 0); }
	const int absX = abs(x());
	const int absY = abs(y());
	if (absX > absY) {
		return Vector2(0, 1);
	}
	if (absX < absY) {
		return Vector2(1, 0);
	}

	if (x() / absX == y() / absY) { return Vector2(1, -1); }
	return Vector2(1, 1);
}

double Vector2F::length() const
{
	return sqrt(m_x*m_x + m_y*m_y);
}

Vector2F Vector2F::operator-(const Vector2F &other) const
{
	return Vector2F(m_x - other.m_x, m_y - other.m_y);
}

Vector2F Vector2F::ofTheSameLengthAs(const Vector2F &other) const
{
	const double len = length();
	if (len == 0) { return *this; }
	return (*this) * (other.length() / len);
}

Vector2 Vector2F::integerCapped() const
{
	int iX = 0;
	if (m_x > 0.5) { iX = 1; }
	else if (m_x < -0.5) { iX = -1; }

	int iY = 0;
	if (m_y > 0.5) { iY = 1; }
	else if (m_y < -0.5) { iY = -1; }

	return Vector2(iX, iY);
}
