#ifndef PARSEDNODE_H
#define PARSEDNODE_H

#include "Node.h"

class ParsedNode: public Node
{
public:
	typedef int Id;

	ParsedNode(Id id): m_id(id) {}
	void setNode(const NodePtr &node) const { m_node = node; }

	virtual Type type() const override { return m_node->type(); }
	virtual NodePtr eval() const override { return m_node->eval(); }
	virtual NodePtr pass(const NodePtr &arg) const override { return m_node->pass(arg); }

private:
	Id m_id;
	mutable NodePtr m_node;
};

#endif // PARSEDNODE_H
