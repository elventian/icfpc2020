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
	x7 = list[7]->intVal();
}

Vector2 ShipState::nextTickPos() const
{
	Vector2 newVelocity = velocity + position.getGravity();
	return position + newVelocity;
}

Vector2 ShipState::getThrustToKeepOrbit(int orbitRadius) const
{
	if (position.chebyshevDist({0, 0}) >= orbitRadius) { return Vector2(0, 0); }

	const Vector2 forceToIncreaseRadius = position.getGravity() * -1;

	// Choose normal to gravity with direction closer to velocity.

	// If velocity == 0, this line arbitrary defines initial rotation direction.
	Vector2 gravNormal = position.getSomeNormalToGravity();

	const Vector2 oppositeGravNormal = gravNormal * -1;
	if (velocity.dotProduct(oppositeGravNormal) > velocity.dotProduct(gravNormal)) {
		gravNormal = oppositeGravNormal;
	}

	const Vector2F velocityF = Vector2F(velocity);
	const Vector2F forceToChangeDirF =
		Vector2F(gravNormal).ofTheSameLengthAs(velocityF) - velocityF;
	const Vector2 forceToChangeDir = forceToChangeDirF.integerCapped();

	const Vector2 force = forceToIncreaseRadius + forceToChangeDir;
	return force.capped() * -1;
}
