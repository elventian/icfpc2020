#include "Vector2.h"
#include "ConsList.h"
#include <math.h>
#include <limits.h>

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

Vector2 Vector2::getBestDirection() const
{
	int bestProduct = INT_MIN;
	const Vector2 *bestDir = nullptr;
	for (int i=0; i < 8; ++i) {
		const Vector2 &dir = allDirections[i];
		int product = dotProduct(dir);
		if (product > bestProduct) {
			bestProduct	= product;
			bestDir = &dir;
		}
	}
	return *bestDir;
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

Vector2 Vector2::getCodirectionalNormalToGravity(const Vector2 &direction) const
{
	Vector2 gravNormal = getSomeNormalToGravity();
	const Vector2 oppositeGravNormal = gravNormal * -1;
	if (direction.dotProduct(oppositeGravNormal) > direction.dotProduct(gravNormal)) {
		gravNormal = oppositeGravNormal;
	}
	return gravNormal;
}

double Vector2F::length() const
{
	return sqrt(m_x*m_x + m_y*m_y);
}

Vector2 Vector2F::roundedVector2() const
{
	return Vector2(round(m_x), round(m_y));
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

Vector2F Vector2F::normalized() const
{
	const double len = length();
	if (len == 0) { return Vector2F(0, 0); }
	return Vector2F(m_x / len, m_y / len);
}

Vector2F Vector2F::projection(const Vector2F &base) const
{
	const Vector2F projUnit = base.normalized();
	const double projectionLength = dotProduct(projUnit);
	return projUnit * projectionLength;
}
