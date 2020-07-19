#include "GameState.h"
#include "Game.h"

GameState::GameState()
{
	
}

void GameState::update(const std::string &newState)
{
	std::cout << newState << std::endl;
	const char *str = newState.c_str();
	//bool delimiter = true;
	//bool listEnd = false;
	
	if (newState == "1101000") {
		std::cout << "BAD STATE" << std::endl;
		return;
	}
	
	for (unsigned i = 0; i < newState.length(); i++) {
		if (str[i] == '1' && str[i + 1] == '1') {
			/*if (delimiter) { std::cout << " [ "; }
			else {std::cout << ", "; }*/
			std::cout << "|";
			//delimiter = true;
			i += 1;
			continue;
		}
		else if (str[i] == '0' && str[i + 1] == '0') {
			//listEnd = true;
			std::cout << "*";
			i += 1;
			continue;
		}
		//delimiter = false;
		//listEnd = false;
		int length = 0;
		int64_t value = Game::intFromLinear(str + i, length);
		std::cout << value << '.';
		//std::cout << std::endl << str + i + length << std::endl;
		i += length - 1;
	}
	
	
	/*int i = 0;
	do {
		std::cout << Game::nextIntFromLinear(str, i) << std::endl;
	} while (i);
	
	std::cout << std::endl;*/
}
