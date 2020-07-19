#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <map>

#include "ConsTree.h"
#include "ShipState.h"

class GameState
{
public:
	enum Stage {
		NotStarted,
		Started,
		Finished,
	};

	GameState(const ConsTree &response);

	bool requestWasSuccess;
	Stage stage;
	ShipState::Role role;
	int gameTick;

	std::map<int, ShipStatePtr> ships; // Key is ship id.
};

#endif // GAMESTATE_H
