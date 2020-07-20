#include "Vector2.h"
#include "ConsList.h"
#include <math.h>

Vector2::Vector2(const ConsList *list)
{
	x() = (*list)[0]->intVal();
	y() = (*list)[1]->intVal();
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
