#ifndef COMMANDS_H
#define COMMANDS_H

#include <string>
#include <list>

class Command
{
public:
	virtual std::string toLinear() const = 0;
};

class Accelerate: public Command
{
public:
	Accelerate(int shipId, int x, int y): m_shipId(shipId), m_x(x), m_y(y){}
	std::string toLinear() const override;
private:
	int m_shipId;
	int m_x;
	int m_y;
};

class CommandList: public std::list<Command *>
{
public:
	std::string toLinear() const;
};


#endif // COMMANDS_H
