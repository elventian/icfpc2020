#include "DiscrCoord2.h"
#include <algorithm>
#include <cmath>

int DiscrCoord2::manhDist(const DiscrCoord2 &other) const {
	int dx = std::abs(x() - other.x());
	int dy = std::abs(y() - other.y());
	return dx + dy;
}


int DiscrCoord2::squaredDist(const DiscrCoord2 &other) const {
	int dx = x() - other.x();
	int dy = y() - other.y();
	return dx*dx + dy*dy;
}

int DiscrCoord2::dist(const DiscrCoord2 &other) const { 
	return sqrt(squaredDist(other)); 
}


int DiscrCoord2::chebyshevDist(const DiscrCoord2 &other) const {
	int dx = std::abs(x() - other.x());
	int dy = std::abs(y() - other.y());
	return std::max(dx, dy);
}

DiscrCoord2 DiscrCoord2::toGrid(int gridStep) const {
	DiscrCoord2 res = *this / gridStep;
	if (c[X] < 0 && (c[X] % gridStep) != 0) res.c[X]--;
	if (c[Y] < 0 && (c[Y] % gridStep) != 0) res.c[Y]--;
	return res * gridStep;
}

DiscrCoord2 DiscrCoord2::toInGrid(int gridStep) const {
	DiscrCoord2 onGrid = toGrid(gridStep);
	return *this - onGrid;
}

std::vector<DiscrCoord2> DiscrCoord2::getAdjacent() const {
	std::vector<DiscrCoord2> res;
	res.push_back(DiscrCoord2(x() - 1, y()));
	res.push_back(DiscrCoord2(x() + 1, y()));
	res.push_back(DiscrCoord2(x(), y() - 1));
	res.push_back(DiscrCoord2(x(), y() + 1));
	return res;
}


std::ostream &operator<<(std::ostream &strm, const DiscrCoord2 &coord) {
	strm << "(" << coord.x() << ", " << coord.y() << ")";
	return strm;
}


std::istream &operator>>(std::istream &strm, DiscrCoord2 &coord) {
	strm >> (int &)coord.x() >> (int &)coord.y();
	return strm;
}
