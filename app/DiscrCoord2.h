#ifndef DISCRCOORD2_H
#define DISCRCOORD2_H

#include <iostream>
#include <vector>
#include <list>
#include <set>


class DiscrCoord2 {
public:
	enum Axis {	X, Y, AxesNum };
	
	DiscrCoord2() { c[X] = c[Y] = 0; }
	DiscrCoord2(int x, int y) { c[X] = x; c[Y] = y; }
	DiscrCoord2(const DiscrCoord2 &other) { *this = other; }
	
	int operator[](int axis) const { return c[axis]; }
	int &operator[](int axis) { return c[axis]; }
	int x() const { return c[X]; }
	int y() const { return c[Y]; }
	int &x() { return c[X]; }
	int &y() { return c[Y]; }
	bool operator<(const DiscrCoord2& other) const { return x() < other.x() ||
		(x() == other.x() && y() < other.y()); }
	bool operator!=(const DiscrCoord2& other) const { return x() != other.x() || y() != other.y(); }
	bool operator==(const DiscrCoord2 &other) const { return x() == other.x() && y() == other.y(); }
	DiscrCoord2 operator+(const DiscrCoord2 &other) const {
		return DiscrCoord2(x() + other.x(), y() + other.y());
	}
	DiscrCoord2 operator+=(const DiscrCoord2 &other) {
		*this = other + *this;
		return *this;
	}
	DiscrCoord2 operator-(const DiscrCoord2 &other) const {
		return DiscrCoord2(x() - other.x(), y() - other.y());
	}
	DiscrCoord2 operator+(const int n) const { return DiscrCoord2(x() + n, y() + n); }
	DiscrCoord2 operator*(int mult) const { return DiscrCoord2(x()*mult, y()*mult); }
	DiscrCoord2 operator*(const DiscrCoord2 &mult) const { return DiscrCoord2(x()*mult.x(), y()*mult.y()); }
	DiscrCoord2 operator/(int divisor) const { return DiscrCoord2(x()/divisor, y()/divisor); }
	bool isZero() const { return x() == 0 && y() == 0; }
	int manhDist(const DiscrCoord2 &other) const;
	int squaredDist(const DiscrCoord2 &other) const;
	int dist(const DiscrCoord2 &other) const;
	int chebyshevDist(const DiscrCoord2 &other) const;
	double squaredDistToLine(const DiscrCoord2 &linePoint1, const DiscrCoord2 &linePoint2);
	int dotProduct(const DiscrCoord2 &other) const { return x() * other.x() + y() * other.y(); }
	DiscrCoord2 toGrid(int gridStep) const;
	DiscrCoord2 toInGrid(int gridStep) const;
	std::vector<DiscrCoord2> getAdjacent() const;
	bool isAdjacent(const DiscrCoord2 &other) const { return manhDist(other) == 1; }
	bool isInBoundaries(const DiscrCoord2 &from, const DiscrCoord2 &to) const { 
		return x()>= from.x() && y() >= from.y() && 
			   x()<= to.x() && y() <= to.y();
	}
	DiscrCoord2 &normalize() {
		if (x()) { x() = x() / abs(x()); }
		if (y()) { y() = y() / abs(y()); }
		return *this;
	}
	
	private:
		int c[AxesNum];
};


std::ostream &operator<<(std::ostream &strm, const DiscrCoord2 &coord);
std::istream &operator>>(std::istream &strm, DiscrCoord2 &coord);


typedef DiscrCoord2 Size2;
typedef std::vector<DiscrCoord2> CoordsVector;
typedef std::list<DiscrCoord2> CoordsList;
typedef std::set<DiscrCoord2> CoordsSet;


#endif // DISCRCOORD2_H
