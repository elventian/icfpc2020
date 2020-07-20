#include "Commands.h"
#include "Game.h"


std::string CommandList::toLinear() const
{
	std::string res;
	for (const Command *c: *this) {
		res += "11";
		res += c->toLinear();
	}
	res += "00";
	return res;
}

CommandList::~CommandList()
{
	for (Command *cmd: *this) {
		delete cmd;
	}
}

std::string Accelerate::toLinear() const
{
	//(0, shipId, vector)
	std::list<int64_t> list;
	list.push_back(0);
	list.push_back(m_shipId);
	return Game::listToLinear(list, Game::vectorToLinear(m_coord));
}

std::string Detonate::toLinear() const
{
	//(1, shipId)
	std::list<int64_t> list;
	list.push_back(1);
	list.push_back(m_shipId);
	return Game::listToLinear(list);
}

std::string Shoot::toLinear() const
{
	//(2, shipId, target, x3)
	std::list<int64_t> list;
	list.push_back(2);
	list.push_back(m_shipId);
	
	return Game::listToLinear(list, Game::vectorToLinear(m_target) + 
		"11" + Game::intToLinear(m_x3));
}

std::string Duplicate::toLinear() const
{
	//(3, shipId, (fuel, x1, x2, cloneCount))
	std::list<int64_t> list;
	list.push_back(3);
	list.push_back(m_shipId);
	
	std::list<int64_t> cloneParams;
	cloneParams.push_back(m_fuel);
	cloneParams.push_back(m_x0);
	cloneParams.push_back(m_x1);
	cloneParams.push_back(m_clones);
	return Game::listToLinear(list, Game::listToLinear(cloneParams));
}
