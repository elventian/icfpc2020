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
	virtual NodePtr calculate() const = 0;

protected:
	Node() {}

	NodePtr thisAsNodePtr() const { return NodePtr(this); }
};

class Nil: Node
{
public:
	Nil() {}
	virtual Type type() const override { return Type::Nil; }
	virtual NodePtr calculate() const override { return thisAsNodePtr(); }
};

class Int: Node
{
public:
	Int(int value): m_value(value) {}
	virtual Type type() const override { return Type::Int; }
	virtual NodePtr calculate() const override {return thisAsNodePtr(); }

const int m_value;
};

#endif // NODE_H
