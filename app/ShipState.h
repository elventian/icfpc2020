#ifndef SHIPSTATE_H
#define SHIPSTATE_H

#include <memory>

#include "Vector2.h"

class ConsList;

class ShipState
{
public:
	enum Role {
		Attacker = 0,
		Defender = 1,
	};

	ShipState(const ConsList *shipList);

	Vector2 nextTickPos() const; // If no thrust expected.
	Vector2 getThrustToHover() const { return position.getGravity(); }
	Vector2 getThrustToKeepOrbit(int orbitRadius) const;

	Role role;
	int id;
	Vector2 position;
	Vector2 velocity;
	int fuel; // checkerboard
	int horizCounter; // unknown
	int health; // vertical counter
	int tunnelCounter; // unknown
	int heating;
	int maxHeating;
	int clonesCount; // Unknown, seems to be always 1.
};

typedef std::shared_ptr<ShipState> ShipStatePtr;

#endif // SHIPSTATE_H
