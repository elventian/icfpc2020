#ifndef NODE_H
#define NODE_H

#include "Type.h"

#include <memory>

class Node;

typedef std::shared_ptr<const Node> NodePtr;

class Node
{
public:
	virtual Type type() const = 0;
	virtual NodePtr eval() const = 0;
	virtual NodePtr pass(const NodePtr &arg) const = 0;

protected:
	Node() {}
};

class Nil: public Node
{
public:
	Nil() {}
	virtual Type type() const override { return Type::Nil; }
	virtual NodePtr eval() const override { return sharedNil; }
	virtual NodePtr pass(const NodePtr &) const override { return nullptr; }

private:
	static const NodePtr sharedNil;
};

class Int: public Node
{
public:
	Int(int value): m_value(value) {}
	virtual Type type() const override { return Type::Int; }
	virtual NodePtr eval() const override
	{
		return NodePtr(static_cast<const Node *>(new Int(m_value)));
	}
	virtual NodePtr pass(const NodePtr &) const override { return nullptr; }

	const int m_value;
};

#endif // NODE_H
