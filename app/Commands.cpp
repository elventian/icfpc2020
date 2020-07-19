#include "Commands.h"
#include "Game.h"

std::string Accelerate::toLinear() const
{
	//(0, shipId, vector)
	std::list<int64_t> list;
	list.push_back(0);
	list.push_back(m_shipId);
	return Game::listToLinear(list, Game::vectorToLinear(m_x, m_y));
}

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
