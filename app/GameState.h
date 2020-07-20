#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <map>

#include "ConsTree.h"
#include "ShipState.h"
#include "Vector2.h"

class GameState
{
public:
	enum Stage {
		NotStarted,
		Started,
		Finished,
	};

	GameState(const ConsTree &response);
	Vector2 getVectorToHover() const;
	int getMyShipId() const;
	const ShipStatePtr &getMyShip() const;

	bool requestWasSuccess;
	Stage stage;
	ShipState::Role role;
	int gameTick = 0;

	std::map<int, ShipStatePtr> ships; // Key is ship id.
};

#endif // GAMESTATE_H
