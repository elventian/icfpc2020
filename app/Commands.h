#ifndef COMMANDS_H
#define COMMANDS_H

#include <string>
#include <list>
#include <Vector2.h>

class Command
{
public:
	virtual std::string toLinear() const = 0;
	virtual ~Command() {}
};

class Accelerate: public Command
{
public:
	Accelerate(int shipId, Vector2 coord): m_shipId(shipId), m_coord(coord) {}
	Accelerate(int shipId): m_shipId(shipId) {}
	std::string toLinear() const override;
	void setCoord(Vector2 coord) { m_coord = coord; }
private:
	int m_shipId;
	Vector2 m_coord;
};

class Detonate: public Command
{
public:
	Detonate(int shipId): m_shipId(shipId) {}
	std::string toLinear() const override;
private:
	int m_shipId;
};

class Shoot: public Command
{
public:
	Shoot(int shipId): m_shipId(shipId) { }
	Shoot(int shipId, Vector2 target, int x3): 
		m_shipId(shipId), m_target(target), m_x3(x3){}
	std::string toLinear() const override;
	
	void setTarget(Vector2 coord) { m_target = coord; }
	void setWeapon(int id) { m_x3 = id; } //TODO: check other types
private:
	int m_shipId;
	Vector2 m_target;
	int m_x3;
};

class Duplicate: public Command
{
public:
	Duplicate(int shipId): m_shipId(shipId) {}
	std::string toLinear() const override;
private:
	int m_shipId;
};


class CommandList: public std::list<Command *>
{
public:
	std::string toLinear() const;
	~CommandList();
};


#endif // COMMANDS_H
