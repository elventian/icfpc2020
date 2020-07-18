#include "Functions.h"

#define INT(node)  dynamic_cast<const Int *>(node.get())->m_value
#define NODE(child) NodePtr(static_cast<const Node *>(child))

NodePtr Sum::evalFull() const
{
	NodePtr x0 = m_args[0]->eval();
	NodePtr x1 = m_args[1]->eval();
	assert(x0->type() == Type::Int);
	assert(x1->type() == Type::Int);
	return NODE(new Int(INT(x0) + INT(x1)));
}

NodePtr Product::evalFull() const
{
	NodePtr x0 = m_args[0]->eval();
	NodePtr x1 = m_args[1]->eval();
	assert(x0->type() == Type::Int);
	assert(x1->type() == Type::Int);
	return NODE(new Int(INT(x0) * INT(x1)));
}

NodePtr IntDivision::evalFull() const
{
	NodePtr x0 = m_args[0]->eval();
	NodePtr x1 = m_args[1]->eval();
	assert(x0->type() == Type::Int);
	assert(x1->type() == Type::Int);
	return NODE(new Int(INT(x0) / INT(x1)));
}

NodePtr Equality::evalFull() const
{
	NodePtr x0 = m_args[0]->eval();
	NodePtr x1 = m_args[1]->eval();
	assert(x0->type() == Type::Int);
	assert(x1->type() == Type::Int);
	if (INT(x0) == INT(x1)) {
		return NODE(new True());
	}
	else {
		return NODE(new False());
	}
}

NodePtr True::evalFull() const
{
	return m_args[0];
}

NodePtr False::evalFull() const
{
	return m_args[1];
}

NodePtr Less::evalFull() const
{
	NodePtr x0 = m_args[0]->eval();
	NodePtr x1 = m_args[1]->eval();
	assert(x0->type() == Type::Int);
	assert(x1->type() == Type::Int);
	if (INT(x0) < INT(x1)) {
		return NODE(new True());
	}
	else {
		return NODE(new False());
	}
}

NodePtr Negate::evalFull() const
{
	NodePtr x0 = m_args[0]->eval();
	assert(x0->type() == Type::Int);
	return NODE(new Int(INT(x0) * -1));
}

//CombS(f,g,x) = f(x)(g(x)) 
NodePtr CombS::evalFull() const
{
	const NodePtr &x0 = m_args[0];
	const NodePtr &x1 = m_args[1];
	const NodePtr &x2 = m_args[2];
	
	NodePtr fx = x0->pass(x2);
	NodePtr gx = x1->pass(x2);
	return fx->pass(gx);	
}

//CombC(f, x, y) = f(y, x)
NodePtr CombC::evalFull() const
{
	const NodePtr &x0 = m_args[0];
	const NodePtr &x1 = m_args[1];
	const NodePtr &x2 = m_args[2];
	
	return x0->pass(x2)->pass(x1);
}

//CombB(f,g,x) = f(g(x))
NodePtr CombB::evalFull() const
{
	const NodePtr &x0 = m_args[0];
	const NodePtr &x1 = m_args[1];
	const NodePtr &x2 = m_args[2];
	
	return x0->pass(x1->pass(x2));
}

NodePtr CombI::evalFull() const
{
	return m_args[0];
}

NodePtr Cons::evalFull() const
{
	const NodePtr &x0 = m_args[0];
	const NodePtr &x1 = m_args[1];
	const NodePtr &x2 = m_args[2];
	
	return x2->pass(x0)->pass(x1);
}

NodePtr Car::evalFull() const
{
	const NodePtr &x0 = m_args[0];
	
	return x0->pass(NODE(new True()));
}

NodePtr Cdr::evalFull() const
{
	const NodePtr &x0 = m_args[0];
	
	return x0->pass(NODE(new False()));
}

NodePtr IsNil::evalFull() const
{
	NodePtr x0 = m_args[0]->eval();
	
	if (x0->type() == Type::Nil) {
		return NODE(new True());
	}
	else {
		return NODE(new False());
	}
}
