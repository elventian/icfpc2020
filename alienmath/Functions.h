#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "Function.h"

class Sum: public Function
{
public:
	Sum(const Args &args): Function(args) {}
	virtual Type type() const override { return Type::Sum; }
	virtual unsigned maxArgs() const override { return 2; }

protected:
	virtual NodePtr calcFull() const override { return thisAsNodePtr(); } // TODO: Implement
};

#endif // FUNCTIONS_H
