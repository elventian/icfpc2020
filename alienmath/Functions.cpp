#include "Functions.h"

NodePtr Sum::evalFull() const
{
	NodePtr x0 = m_args[0]->eval();
	NodePtr x1 = m_args[1]->eval();
	assert(x0->type() == Type::Int);
	assert(x1->type() == Type::Int);
	return NodePtr(static_cast<const Node *>(new Int(
		dynamic_cast<const Int *>(x0.get())->m_value
		+ dynamic_cast<const Int *>(x1.get())->m_value)));
}
