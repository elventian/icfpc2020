#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <list>
#include "httplib.h"

class Game
{
public:
	Game(const std::string &serverUrl, const std::string &playerKey);
	void parseState(const std::string &state);
	int64_t intFromLinear(const char *str, int &length) const;
	std::string intToLinear(int64_t value) const;
	std::string listToLinear(const std::list<int64_t> &list) const;
private:
	httplib::Client *m_client;
	const std::string m_postUrl;
	const std::string m_playerKey;
	
	void join();
};

#endif // GAME_H
