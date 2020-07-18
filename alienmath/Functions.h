#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "Function.h"

#define INT(node)  dynamic_cast<const Int *>((node).get())->m_value
#define NODE(child) NodePtr(static_cast<const Node *>(child))

#define DEF_FUNC_CLASS(_name, _maxArgs) \
class _name: public Function \
{ \
public: \
	_name() {} \
	_name(const Args &args): Function(args) {} \
	virtual Type type() const override { return Type::_name; } \
	virtual unsigned maxArgs() const override { return _maxArgs; } \
	virtual NodePtr evalFull() const override; \
protected: \
	virtual Function *clone(const Args &args) const override { return new _name(args); } \
};

DEF_FUNC_CLASS(Sum,         2)
DEF_FUNC_CLASS(Product,     2)
DEF_FUNC_CLASS(IntDivision, 2)
DEF_FUNC_CLASS(Equality,    2)
DEF_FUNC_CLASS(False,       2)
DEF_FUNC_CLASS(True,        2)
DEF_FUNC_CLASS(Less,        2)
DEF_FUNC_CLASS(Negate,      1)
DEF_FUNC_CLASS(CombS,       3)
DEF_FUNC_CLASS(CombC,       3)
DEF_FUNC_CLASS(CombB,       3)
DEF_FUNC_CLASS(CombI,       1)
DEF_FUNC_CLASS(Cons,        3)
DEF_FUNC_CLASS(Car,         1)
DEF_FUNC_CLASS(Cdr,         1)
DEF_FUNC_CLASS(IsNil,       1)
DEF_FUNC_CLASS(Is0,         3)


#endif // FUNCTIONS_H
