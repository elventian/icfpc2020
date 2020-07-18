#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "Function.h"

class Sum: public Function
{
public:
	Sum() {}
	virtual Type type() const override { return Type::Sum; }
	virtual unsigned maxArgs() const override { return 2; }
	virtual NodePtr evalFull() const override
	{
		NodePtr x0 = m_args[0]->eval();
		NodePtr x1 = m_args[1]->eval();
		assert(x0->type() == Type::Int);
		assert(x1->type() == Type::Int);
		return NodePtr(static_cast<const Node *>(new Int(
			dynamic_cast<const Int *>(x0.get())->m_value
			+ dynamic_cast<const Int *>(x1.get())->m_value)));
	}
};

#endif // FUNCTIONS_H
