#ifndef APPLY_H
#define APPLY_H

#include "Node.h"

class Apply: public Node
{
public:
	Apply() {}
	void setLeft(const NodePtr &left) { m_left = left; }
	void setRight(const NodePtr &right) { m_right = right; }
	void determineApType() const;

	virtual Type type() const override { return Type::Apply; }
	virtual NodePtr eval() const override;
	virtual NodePtr pass(const NodePtr &arg) const override;

private:
	enum class ApType {
		Any,
		//Func,
		HalfPair,
		Pair,
	};

	NodePtr m_left;
	NodePtr m_right;
	mutable ApType m_apType = ApType::Any;
};

#endif // APPLY_H
