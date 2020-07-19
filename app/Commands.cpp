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
	//list.push_back(m_shipId);
	
	return Game::listToLinear(list, Game::vectorToLinear(m_target) + 
		"11" + Game::intToLinear(m_x1) +
		"11" + Game::intToLinear(m_x2) +
		"11" + Game::intToLinear(m_x3));
}

std::string UnknownCommand::toLinear() const
{
	//(3, shipId, x1)
	std::list<int64_t> list;
	list.push_back(3);
	list.push_back(m_shipId);
	
	return Game::listToLinear(list);
}
