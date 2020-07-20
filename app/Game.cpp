#include "Game.h"
#include "Commands.h"
#include "GameState.h"
#include "Commands.h"
#include "ConsTree.h"
#include <math.h>
#include <regex>
#include "httplib.h"
#include <fstream>

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
	//state = new GameState();
}

void Game::run()
{
	const std::string joinResponseLin = join();
	std::cout << ConsTree(joinResponseLin).root()->printable() << std::endl;
	const std::string startResponse = start();
	ConsTree startTree = ConsTree(startResponse);
	std::cout << startTree.root()->printable() << std::endl;
	GameState state = GameState(startTree);
	for (int i = 0; i < maxTurns; i++) {
		CommandList commands;
		//set commands for every owned ship
		for (auto shipPair: state.ships) {
			ShipStatePtr &ship = shipPair.second;
			if (ship->role == state.role) {
				//Vector2 thrust = ship->getThrustToHover();
				Vector2 thrust = ship->getThrustToKeepOrbit(32, 48);
				commands.push_back(new Accelerate(ship->id, thrust));
				/*if (i == 6) {
					commands.push_back(
						new Duplicate(ship->id, ship->fuel/2, ship->horizCounter / 2, ship->health / 2));
				}*/
				Vector2 enemyPos = state.getClosestTarget(ship->position);
				int distToEnemy = ship->position.chebyshevDist(enemyPos);
				if (distToEnemy <= 36) {
					commands.push_back(new Shoot(ship->id, enemyPos, 4));
				}
				/*if (ship->role == ShipState::Attacker && distToEnemy <= 8 && state.getEnemyNum() == 1) {
					commands.push_back(new Detonate(ship->id));
				}*/
			}
		}
		//shoot->setTarget(Vector2(0,0)); //TODO
		//shoot->setWeapon(5);
		const std::string &response = sendCommands(commands);
		state = GameState(ConsTree(response));
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

int64_t Game::intFromLinear(const std::string &linear)
{
	int length;
	return intFromLinear(linear.c_str(), length);
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

std::string Game::vectorToLinear(const Vector2 &coord)
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

std::string Game::join() const
{
	//(2, playerKey, (...unknown list...))
	std::list<int64_t> list;
	list.push_back(2);
	list.push_back(std::stol(m_playerKey));
	const std::string &joinCmd = listToLinear(list, listToLinear());
	return sendRequest(joinCmd);
	//state->update();
}

std::string Game::start() const
{
	//(3, playerKey, (x0, x1, x2, x3))
	std::list<int64_t> list;
	list.push_back(3);
	list.push_back(std::stol(m_playerKey));
	std::list<int64_t> undefVars;
	//int x0 = 254, x1 = 3, x2 = 3, x3 = 1; - heat of thrust usage (+5/turn). when reach maximum - drastically increases
	//int x0 = 270, x1 = 30, x2 = 10, x3 = 1; //fail to start
	//98,70,11,1
	//98, 3, 22, 1 - fail to start
	//270, 10, 3, 1 - started, overheat of thrust usage (+5/turn)
	//256, 5, 13, 1 - miniks head - no heat of thrust usage
	//98 0 0 1 - when fuel becomes 0 - die!
	//98 5 0 1 - overheat of thrust usage (+8/turn) but not die when fuel 0
	//134 64 10 1 - Unagi: fail to start!
	//98 0 5 1 - overheat of thrust usage (+3/turn), when no fuel - start cool down, cannot shoot
	//98 5 5 1 (+3/turn)
	//98 10 10 1 - no overheat
	
	int fuel = 256, x1 = 5, x2 = 13, clonesCount = 1;
	undefVars.push_back(fuel);
	undefVars.push_back(x1);
	undefVars.push_back(x2);
	undefVars.push_back(clonesCount);
	const std::string &cmd = listToLinear(list, listToLinear(undefVars));
	return sendRequest(cmd);
}

std::string Game::sendCommands(const CommandList &cmdList) const
{
	std::list<int64_t> list;
	list.push_back(4);
	list.push_back(std::stol(m_playerKey));
	const std::string &cmd = listToLinear(list, cmdList.toLinear());
	
	std::cout << ConsTree(cmd).root()->printable() << std::endl;
	return sendRequest(cmd);
}

std::string Game::sendRequest(const std::string &req) const
{
	std::cout << "Send command: " << req << std::endl;
	if (m_offlineMode) {
		static int calls = 0;
		calls++;
		return "11011000011101100001111101111000010000000011010111101111000100000000011011000011101110010000000011110111000010000110111010000000001111011110000100000000110111000010000110110100011011000010000111101011110111000010000110111010000000001111111101100001110101111011100011000010110000100101111010010111101111000010000000011011100001000011011010001101100001001101011011100100000011011000010011000011111101011011000011111101100011000001110000100101111010010111101110111111101101100011110110001111011000010011010110111001000000110110000100110000000000";
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
