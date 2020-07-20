#include "ShipState.h"
#include "ConsList.h"
#include <math.h>

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
	cloneCounter = counters[3]->intVal();

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
	// If velocity is zero or parallel fravity, go out of planet perpendicular to gravity.
	if (position.getSomeNormalToGravity().dotProduct(velocity)) {
		return Vector2(position.getCodirectionalNormalToGravity(position)
			+ (position.getGravity() * -1)).capped() * -1;
	}

	const bool dangerousApproaching =
		(velocity.dotProduct(position.getGravity()) > 0)
		&& (Vector2(0, 0).squaredDistToLine(position, position + velocity) <=
			planetRadius * planetRadius);

	if (!dangerousApproaching) {
		const Vector2 prevPosition = position - velocity;
		const bool approachingPlanet =
			position.squaredDist({0, 0}) <= prevPosition.squaredDist({0, 0});
		const int radius = approachingPlanet? greaterRadius : lesserRadius;
		// 2 is sqrt(2) squared.
		if (position.chebyshevDist({0, 0}) >= 2 * radius) { return Vector2(0, 0); }
	}

	const Vector2 forceToIncreaseRadius = position.getGravity() * -1;

	Vector2 gravNormal(0, 0);
	const bool velocityAcceptable = velocity.chebyshevDist({0, 0}) <= 7;
	if (dangerousApproaching || velocityAcceptable) {
		gravNormal = position.getCodirectionalNormalToGravity(velocity);
	}

	const Vector2 force = forceToIncreaseRadius + gravNormal;
	return force.capped() * -1;
}

Vector2 ShipState::getThrustToKeepOrbitOrApproach(
	int lesserRadius, int greaterRadius, const ShipState &target) const
{
	const Vector2 thrust = getThrustToKeepOrbit(lesserRadius, greaterRadius);
	if (!thrust.isZero()) { return thrust; }

	// Don't play approach games too close to border.
	if (position.chebyshevDist({0, 0}) >= 96) { return Vector2(0, 0); }

	// Approach will happen soon without help or never if velocities are opposite.
	if (velocity.dotProduct(target.velocity) < 0) { return Vector2(0, 0); }

	const Vector2 toTarget = target.nextTickPos() - position;
	const Vector2F toTargetF = Vector2F(toTarget);
	const double gravityAffinity =
		toTargetF.dotProductNormalized(position.getGravity());
	const Vector2 gravNormal = position.getCodirectionalNormalToGravity(toTarget);

	// 2.0 is empiric value.
	const bool approachWorth =
		(gravityAffinity <= 0)
		|| toTargetF.dotProductNormalized(gravNormal) >= 2.0 * gravityAffinity;
	if (!approachWorth) { return Vector2(0, 0); }

	const Vector2 projection = Vector2F(toTarget).projection(gravNormal).roundedVector2();
	const Vector2 accel = projection.getBestDirection();

	// If approaching would accelerate us even more at too high velocity, don't approach.
	if (accel.dotProduct(velocity) > 0 && velocity.chebyshevDist({0, 0}) > 7) {
		return Vector2(0, 0);
	}
	return accel * -1;
}
