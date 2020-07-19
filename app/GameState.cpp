#include <iostream>

#include "GameState.h"
#include "Game.h"

GameState::GameState(const ConsTree &response)
{
	const ConsList &list = *response.root()->asList();

	requestWasSuccess = list[0]->intVal();
	stage = (Stage)list[1]->intVal();

	const ConsList &staticGameInfo = *list[2]->asList();
	role = (ShipState::Role)staticGameInfo[1]->intVal();

	const ConsList &gameState = *list[3]->asList();
	gameTick = gameState[0]->intVal();

	const ConsList &shipList = *gameState[2]->asList();
	for (const ConsNodePtr &node: shipList) {
		ShipState *ship = new ShipState(node->asList());
		ShipStatePtr shipPtr(ship);
		ships[ship->id] = shipPtr;
	}
}

Vector2 GameState::getVectorToHover() const
{
	Vector2 mycoord = getMyShip()->position;
	Vector2 thrust = mycoord.normalize() * Vector2(-1, -1);
	if (abs(mycoord.x()) > abs(mycoord.y())) { return Vector2(thrust.x(), 0); }
	return Vector2(0, thrust.y());
}

int GameState::getMyShipId() const
{
	for (auto shipPair: ships) {
		ShipStatePtr &ship = shipPair.second;
		if (ship->role == role) {
			return ship->id;
		}
	}
	return 0;
}

const ShipStatePtr &GameState::getMyShip() const
{
	return ships.at(getMyShipId());
}
