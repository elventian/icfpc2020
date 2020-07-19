#include <iostream>
#include <string>
#include "Game.h"

int main(int argc, char* argv[])
{
	bool offline = (argc == 4);
	const std::string serverUrl(argv[1]);
	const std::string playerKey(argv[2]);

	std::cout << "ServerUrl: " << serverUrl << "; PlayerKey: " << playerKey << std::endl;
	Game game(serverUrl, playerKey, offline);
	game.run();
	
	return 0;
}

