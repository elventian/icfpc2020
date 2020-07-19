#include "Vector2.h"
#include "ConsList.h"

Vector2::Vector2(const ConsList *list)
{
	x() = (*list)[0]->intVal();
	y() = (*list)[1]->intVal();
}
