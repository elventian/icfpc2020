#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <list>
#include "Vector2.h"

class GameState;
class CommandList;
class Accelerate;
class Shoot;
namespace httplib {
	class Client;
}

class Game
{
public:
	Game(const std::string &serverUrl, const std::string &playerKey, bool offlineMode);
	void run();
	static int64_t intFromLinear(const char *str, int &length);
	static int64_t intFromLinear(const std::string &linear);
	static int64_t nextIntFromLinear(const char *str, int &i);
	static std::string intToLinear(int64_t value);
	static std::string vectorToLinear(const Vector2 &coord);
	static std::string listToLinear(const std::list<int64_t> &list = std::list<int64_t>(),
		const std::string &data = "");
private:
	bool m_offlineMode;
	httplib::Client *m_client;
	const std::string m_postUrl;
	const std::string m_playerKey;
	const int maxTurns = 256;
	Accelerate *accelerate;
	Shoot *shoot;
	
	std::string join() const;
	std::string start() const;
	std::string sendCommands(const CommandList &cmdList) const;
	std::string sendRequest(const std::string &req) const;
};

#endif // GAME_H
