#ifndef NODE_H
#define NODE_H

#include "Type.h"

#include <memory>
#include <stdint.h>

class Node;

typedef std::shared_ptr<const Node> NodePtr;

class Node
{
public:
	virtual ~Node() {}
	virtual Type type() const = 0;
	virtual Type typeForParsing() const { return type(); }
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
	Int(int64_t value): m_value(value) {}
	virtual Type type() const override { return Type::Int; }
	virtual NodePtr eval() const override
	{
		return NodePtr(static_cast<const Node *>(new Int(m_value)));
	}
	virtual NodePtr pass(const NodePtr &) const override { return nullptr; }

	const int64_t m_value;
};

#endif // NODE_H
