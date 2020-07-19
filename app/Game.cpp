#include "Game.h"
#include "Commands.h"
#include "GameState.h"
#include "Commands.h"
#include <math.h>
#include <regex>

Game::Game(const std::string &serverUrl, const std::string &playerKey, bool offlineMode): 
	m_offlineMode(offlineMode),
	m_postUrl(serverUrl + "/aliens/send"), m_playerKey(playerKey)
{
	const std::regex urlRegexp("http://(.+):(\\d+)");
	std::smatch urlMatches;
	if (!std::regex_search(serverUrl, urlMatches, urlRegexp) || urlMatches.size() != 3) {
		std::cout << "Unexpected server response:\nBad server URL" << std::endl;
		exit(1);
	}
	if (!m_offlineMode) {
		const std::string serverName = urlMatches[1];
		const int serverPort = std::stoi(urlMatches[2]);
		m_client = new httplib::Client(serverName, serverPort);
	}
	state = new GameState();
}

void Game::run()
{
	join();
	start();
	CommandList commands;
	//commands.push_back(new Accelerate(1, DiscrCoord2(1, 1)));
	//commands2.push_back(new Accelerate(1, DiscrCoord2(-1, -1)));
	//commands.push_back(new Shoot(0, DiscrCoord2(50, 50), 0));
	commands.push_back(new UnknownCommand(0, 0));
	for (int i = 0; i < maxTurns; i++) {
		sendCommands(commands);
	}
}

int64_t Game::intFromLinear(const char *str, int &length)
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

int64_t Game::nextIntFromLinear(const char *str, int &i)
{
	while (str[i] != '\0') {
		if ((str[i] == '1' && str[i + 1] == '1') || (str[i] == '0' && str[i + 1] == '0')) {
			i += 2;
		}
		else {
			int length = 0;
			int64_t value = Game::intFromLinear(str + i, length);
			i += length;
			return value;
		}
	}
	i = 0;
	return 0;
}

std::string Game::intToLinear(int64_t value)
{
	uint64_t uvalue = abs(value);
	int n = 0, width = 3;
	if (uvalue != 0)
	{
		int intWidth = log2(uvalue); //meaning integer part
		n = (intWidth / 4 + 1);
		width = 2 + n + 1 + n * 4;
	}
	char res[width + 1];
	memset(res, '0', sizeof(res));
	res[width] = '\0';
	if (value >= 0) { res[1] = '1';}
	else { res[0] = '1'; }
	for (int i = 0; i < n; i++) {
		res[2 + i] = '1';
	}
	int i = width - 1;
	while (uvalue > 0) {
		if (uvalue & 0x1) {
			res[i] = '1';
		}
		uvalue = uvalue >> 1;
		i--;
	}
	return std::string(res);
}

std::string Game::vectorToLinear(const DiscrCoord2 &coord)
{
	return "11" + intToLinear(coord.x()) + intToLinear(coord.y());
}

std::string Game::listToLinear(const std::list<int64_t> &list, const std::string &data)
{
	std::string linearList;
	for (int64_t value: list) {
		linearList += "11" + intToLinear(value);
	}
	if (!data.empty()) { linearList += "11" + data; }
	linearList += "00";
	return linearList;
}

void Game::join() const
{
	//(2, playerKey, (...unknown list...))
	std::list<int64_t> list;
	list.push_back(2);
	list.push_back(std::stol(m_playerKey));
	const std::string &joinCmd = listToLinear(list, listToLinear());
	sendRequest(joinCmd);
	//state->update();
}

void Game::start() const
{
	//(3, playerKey, (x0, x1, x2, x3))
	std::list<int64_t> list;
	list.push_back(3);
	list.push_back(std::stol(m_playerKey));
	std::list<int64_t> undefVars;
	int x0 = 254, x1 = 0, x2 = 16, x3 = 1;
	undefVars.push_back(x0);
	undefVars.push_back(x1);
	undefVars.push_back(x2);
	undefVars.push_back(x3);
	const std::string &cmd = listToLinear(list, listToLinear(undefVars));
	sendRequest(cmd);
}

void Game::sendCommands(const CommandList &cmdList) const
{
	std::list<int64_t> list;
	list.push_back(4);
	list.push_back(std::stol(m_playerKey));
	const std::string &cmd = listToLinear(list, cmdList.toLinear());
	sendRequest(cmd);
}

std::string Game::sendRequest(const std::string &req) const
{
	std::cout << "Send command: " << req << std::endl;
	if (m_offlineMode) {
		return "11011000011101100001111101111000010000000011010111101111000100000000011011000011101110010000"
		"000011110111000010000110111010000000001111011000011101100001110110000111011000010000111101011110111"
		"000010000110111010000000001111111101100001110101111101100011000010110000101101111010010111101100001"
		"110110000111011000011101100001001101011011100100000011011000010011000011111101011011000011111011100"
		"011000001110000101101111010010111101100001110110000111011000011101100001001101011011100100000011011"
		"0000100110000000000";
	}
	else {
		const std::shared_ptr<httplib::Response> serverResponse = 
			m_client->Post(m_postUrl.c_str(), req.c_str(), "text/plain");
	
		if (!serverResponse) {
			std::cout << "Unexpected server response:\nNo response from server" << std::endl;
			exit(2);
		}
		
		if (serverResponse->status != 200) {
			std::cout << "Unexpected server response:\nHTTP code: " << serverResponse->status
					<< "\nResponse body: " << serverResponse->body << std::endl;
			exit(3);
		}
		std::cout << "Server response: " << serverResponse->body << std::endl;
		return serverResponse->body;
	}
}

