#include <iostream>
#include <string>
#include "Game.h"

int main(int argc, char* argv[])
{
	(void) argc;
	const std::string serverUrl(argv[1]);
	const std::string playerKey(argv[2]);

	std::cout << "ServerUrl: " << serverUrl << "; PlayerKey: " << playerKey << std::endl;
	Game game(serverUrl, playerKey);
	
	return 0;
}

