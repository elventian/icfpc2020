#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <list>

class Game
{
public:
	Game();
	void parseState(const std::string &state);
	int64_t intFromLinear(const char *str, int &length) const;
	std::string intToLinear(int64_t value) const;
	std::string listToLinear(const std::list<int64_t> &list) const;
};

#endif // GAME_H
