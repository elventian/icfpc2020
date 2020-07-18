#ifndef APPLY_H
#define APPLY_H

#include "Node.h"

#define APPLY(node)  dynamic_cast<const Apply *>((node).get())

class Apply: public Node
{
public:
	enum class ApType {
		Any,
		HalfPair,
		Pair,
	};

	Apply() {}
	Apply(NodePtr left, NodePtr right): m_left(left), m_right(right) {}
	Apply(Node *left, Node *right): m_left(NodePtr(left)), m_right(NodePtr(right)) {}
	ApType getAppType() const { return m_apType; }
	bool hasBothChildren() const { return (bool)m_right; }
	void addChild(const NodePtr &child) const;
	void determineApType() const;
	NodePtr &getLeft() const { return m_left; }
	NodePtr &getRight() const { return m_right; }

	virtual Type type() const override { return Type::Apply; }
	virtual NodePtr eval() const override;
	virtual NodePtr pass(const NodePtr &arg) const override;

private:
	mutable NodePtr m_left;
	mutable NodePtr m_right;
	mutable ApType m_apType = ApType::Any;
};

#endif // APPLY_H
