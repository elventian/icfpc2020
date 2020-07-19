#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <list>
#include "httplib.h"

class Game
{
public:
	Game(const std::string &serverUrl, const std::string &playerKey, bool offlineMode);
	void run();
	void parseState(const std::string &state);
	int64_t intFromLinear(const char *str, int &length) const;
	std::string intToLinear(int64_t value) const;
	std::string listToLinear(const std::list<int64_t> &list = std::list<int64_t>(),
		const std::string &data = "") const;
private:
	bool m_offlineMode;
	httplib::Client *m_client;
	const std::string m_postUrl;
	const std::string m_playerKey;
	
	void join() const;
	void start() const;
	std::string sendRequest(const std::string &req) const;
};

#endif // GAME_H
