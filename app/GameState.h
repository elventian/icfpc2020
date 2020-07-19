#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <stdint.h>
#include <string>

class GameState
{
public:
	GameState();
	void update(const std::string &newState);
private:
	int64_t stageId;
	bool isAttacker;
	int64_t staticX0, staticX2, staticX3, staticX4;
	int64_t gameTick;
	int64_t x1;
};

#endif // GAMESTATE_H
