#include "ShipState.h"
#include "ConsList.h"

static constexpr int planetRadius = 16;

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

Vector2 ShipState::getThrustToKeepOrbit(int lesserRadius, int greaterRadius) const
{
	bool dangerousApproaching =
		(velocity.dotProduct(position.getGravity()) > 0)
		&& (Vector2(0, 0).squaredDistToLine(position, position + velocity) <=
			planetRadius * planetRadius);

	if (!dangerousApproaching) {
		const Vector2 prevPosition = position - velocity;
		const bool approachingPlanet =
			position.squaredDist({0, 0}) <= prevPosition.squaredDist({0, 0});
		const int radius = approachingPlanet? greaterRadius : lesserRadius;
		if (position.chebyshevDist({0, 0}) >= radius) { return Vector2(0, 0); }
	}

	const Vector2 forceToIncreaseRadius = position.getGravity() * -1;

	// Choose normal to gravity with direction closer to velocity.

	// If velocity == 0, this line arbitrary defines initial rotation direction.
	Vector2 gravNormal = position.getSomeNormalToGravity();

	const Vector2 oppositeGravNormal = gravNormal * -1;
	if (velocity.dotProduct(oppositeGravNormal) > velocity.dotProduct(gravNormal)) {
		gravNormal = oppositeGravNormal;
	}

	const Vector2 forceToChangeDir = gravNormal;

	const Vector2 force = forceToIncreaseRadius + forceToChangeDir;
	return force.capped() * -1;
}

Vector2 ShipState::getThrustToKeepOrbitOrApproach(
	int lesserRadius, int greaterRadius, const Vector2 &target) const
{
	const Vector2 thrust = getThrustToKeepOrbit(lesserRadius, greaterRadius);
	if (!thrust.isZero()) { return thrust; }

	const Vector2 toTarget = target - position;
	if (toTarget.dotProduct(position.getGravity()) > 0) { return Vector2(0, 0); }

	return Vector2(0, 0); // TODO: Implement.
}
