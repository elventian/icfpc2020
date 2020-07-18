#ifndef APPLY_H
#define APPLY_H

#include "Node.h"

class Apply: public Node
{
public:
	enum class ApType {
		Any,
		HalfPair,
		Pair,
	};

	Apply() {}
	ApType getAppType() const { return m_apType; }
	bool hasBothChildren() const { return (bool)m_right; }
	void addChild(const NodePtr &child) const;
	void determineApType() const;

	virtual Type type() const override { return Type::Apply; }
	virtual NodePtr eval() const override;
	virtual NodePtr pass(const NodePtr &arg) const override;

private:
	mutable NodePtr m_left;
	mutable NodePtr m_right;
	mutable ApType m_apType = ApType::Any;
};

#endif // APPLY_H
