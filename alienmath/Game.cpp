#include "Game.h"
#include <math.h>

Game::Game()
{
	
}

int64_t Game::intFromLinear(const char *str, int &length) const
{
	//parse linear representation
	int n = 0, intWidth;
	while (str[2 + n] == '1') { n++; }
	intWidth = n * 4;
	int64_t value = 0;
	for (int i = 0; i < intWidth; i++) {
		if (str[2 + (n + 1) + i] == '1') {
			value += 1 << (intWidth - i - 1);
		}
	}
	bool linearNegative = str[0] == '1' && str[1] == '0';
	if (linearNegative) { value *= -1; }
	length = 3 + n + n * 4;
	return value;
}

std::string Game::intToLinear(int64_t value) const
{
	int64_t uvalue = abs(value);
	int n = 0, width = 3;
	if (uvalue != 0)
	{
		int intWidth = log2(uvalue); //meaning integer part
		n = (intWidth / 4 + 1);
		width = 2 + n + 1 + n * 4;
	}
	char res[width] = {'0'};
	if (value >= 0) { res[1] = true;}
	else { res[0] = true; }
	for (int i = 0; i < n; i++) {
		res[2 + i] = true;
	}
	int i = width - 1;
	while (uvalue > 0) {
		if (uvalue & 0x1) {
			res[i] = true;
		}
		uvalue = uvalue >> 1;
		i--;
	}
	return std::string(res);
}

std::string Game::listToLinear(const std::list<int64_t> &list) const
{
	std::string linearList;
	for (int64_t value: list) {
		linearList += "11" + intToLinear(value);
	}
	linearList += "00";
	return linearList;
}

void Game::parseState(const std::string &state)
{
	/*const char *str = state.c_str();
	bool delimiter = false;
	bool listEnd = false;
	for (unsigned i = 0; i < state.length(); i++) {
		if (str[i] == '1' && str[i + 1] == '1') {
			if (delimiter) { std::cout << " [ "; }
			else {std::cout << ", "; }
			delimiter = true;
			i += 1;
			continue;
		}
		else if (str[i] == '0' && str[i + 1] == '0') {
			listEnd = true;
			std::cout << " ] ";
			i += 1;
			continue;
		}
		delimiter = false;
		listEnd = false;
		int length = 0;
		int64_t value = intFromLinear(str + i, length);
		std::cout << value;
		std::cout << std::endl << str + i + length << std::endl;
		i += length - 1;
	}*/
}


