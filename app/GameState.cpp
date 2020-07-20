#include <iostream>

#include "GameState.h"
#include "Game.h"

GameState::GameState(const ConsTree &response)
{
	const ConsList &list = *response.root()->asList();

	requestWasSuccess = list[0]->intVal();
	stage = (Stage)list[1]->intVal();
	if (stage == Stage::Finished) { exit(0); }

	const ConsList &staticGameInfo = *list[2]->asList();
	role = (ShipState::Role)staticGameInfo[1]->intVal();

	const ConsList &gameState = *list[3]->asList();
	if (gameState.size() != 3) { return; }
	gameTick = gameState[0]->intVal();

	const ConsList &shipList = *gameState[2]->asList();
	for (const ConsNodePtr &node: shipList) {
		ShipState *ship = new ShipState(node->asList());
		ShipStatePtr shipPtr(ship);
		ships[ship->id] = shipPtr;
		
		std::cout << "new ship " << ship->id << " at " << ship->position << std::endl;
	}
}

ShipStatePtr GameState::getClosestTarget(Vector2 &curCoord) const
{
	bool found = false;
	int curDist = -1;
	ShipStatePtr res;
	for (auto shipPair: ships) {
		ShipStatePtr &ship = shipPair.second;
		if (ship->role != role) {
			Vector2 nextPos = ship->nextTickPos();
			if (!found || curCoord.dist(nextPos) < curDist) {
				found = true;
				curDist = curCoord.dist(nextPos);
				res = ship;
			}
		}
	}
	return res;
}

ShipStatePtr GameState::getTarget(Vector2 &curCoord, int maxDist) const
{
	bool found = false;
	ShipStatePtr res;
	for (auto shipPair: ships) {
		ShipStatePtr &ship = shipPair.second;
		if (ship->role != role) {
			Vector2 nextPos = ship->nextTickPos();
			if (!found || (curCoord.dist(nextPos) < maxDist && 
				((res->maxHeating - res->heating) > (ship->maxHeating - ship->heating) ||
				res->fuel < ship->fuel || curCoord.dist(res->position) > curCoord.dist((ship->position)))))
			{
				found = true;
				res = ship;					
			}
		}
	}
	return res;
}

int GameState::checkSwarm(ShipStatePtr &queen) const
{
	int swarmers = 0;
	for (auto shipPair: ships) {
		ShipStatePtr &ship = shipPair.second;
		if (ship->role != role) {
			if (ship->horizCounter > 5 && ship->health > 5) {
				queen = ship;
			}
			else { swarmers++; }
		}
	}
	return swarmers;
}

int GameState::getEnemyNum() const
{
	int i = 0;
	for (auto shipPair: ships) {
		ShipStatePtr &ship = shipPair.second;
		if (ship->role != role) { i++; }
	}
	return i;
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
