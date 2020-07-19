#ifndef CONSNODE_H
#define CONSNODE_H

#include <string>
#include <memory>

class ConsList;

class ConsNode
{
public:
	enum class Type {
		Int,
		List,
		Vector2, // Represented by ConsList of 2 elements.
	};

	ConsNode() {}
	virtual ~ConsNode() {}
	virtual Type type() const = 0;
	virtual std::string printable() const = 0;

	bool isInt() const { return type() == Type::Int; }
	bool isList() const { return type() == Type::List; }
	bool isVector2() const { return type() == Type::Vector2; }
	int64_t intVal() const; // Returns 0 if this is not ConsInt.
	ConsList *asList(); // Return nullptr if this is not List nor Vector2

protected:

};

typedef std::shared_ptr<ConsNode> ConsNodePtr;

#endif // CONSNODE_H
