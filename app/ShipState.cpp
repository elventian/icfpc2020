#include "ShipState.h"
#include "ConsList.h"

ShipState::ShipState(const ConsList *shipList)
{
	const ConsList &list = *(*shipList)[0]->asList();
	if (shipList->size() == 2) {
		const ConsList &commands = *(*shipList)[1]->asList();
		(void) commands;
	}

	role = (Role)list[0]->intVal();
	id = list[1]->intVal();

	position = Vector2(list[2]->asList());
	velocity = Vector2(list[3]->asList());

	const ConsList &counters = *list[4]->asList();
	fuel = counters[0]->intVal();
	horizCounter = counters[1]->intVal();
	health = counters[2]->intVal();
	tunnelCounter = counters[3]->intVal();

	heating = list[5]->intVal();
	maxHeating = list[6]->intVal();
	clonesCount = list[7]->intVal();
}

Vector2 ShipState::nextTickPos() const
{
	Vector2 newVelocity = velocity + position.getGravity();
	return position + newVelocity;
}
