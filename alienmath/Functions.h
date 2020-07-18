#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "Function.h"

class Sum: public Function
{
public:
	Sum() {}
	virtual Type type() const override { return Type::Sum; }
	virtual unsigned maxArgs() const override { return 2; }
	virtual NodePtr evalFull() const override;
};

class Product: public Function
{
public:
	Product() {}
	virtual Type type() const override { return Type::Product; }
	virtual unsigned maxArgs() const override { return 2; }
	virtual NodePtr evalFull() const override;
};

class IntDivision: public Function
{
public:
	IntDivision() {}
	virtual Type type() const override { return Type::IntDivision; }
	virtual unsigned maxArgs() const override { return 2; }
	virtual NodePtr evalFull() const override;
};

class Equality: public Function
{
public:
	Equality() {}
	virtual Type type() const override { return Type::Equality; }
	virtual unsigned maxArgs() const override { return 2; }
	virtual NodePtr evalFull() const override;
};

class True: public Function
{
public:
	True() {}
	virtual Type type() const override { return Type::True; }
	virtual unsigned maxArgs() const override { return 2; }
	virtual NodePtr evalFull() const override;
};

class Less: public Function
{
public:
	Less() {}
	virtual Type type() const override { return Type::Less; }
	virtual unsigned maxArgs() const override { return 2; }
	virtual NodePtr evalFull() const override;
};

class Negate: public Function
{
public:
	Negate() {}
	virtual Type type() const override { return Type::Negate; }
	virtual unsigned maxArgs() const override { return 2; }
	virtual NodePtr evalFull() const override;
};

class CombS: public Function
{
public:
	CombS() {}
	virtual Type type() const override { return Type::CombS; }
	virtual unsigned maxArgs() const override { return 2; }
	virtual NodePtr evalFull() const override;
};

class CombC: public Function
{
public:
	CombC() {}
	virtual Type type() const override { return Type::CombC; }
	virtual unsigned maxArgs() const override { return 2; }
	virtual NodePtr evalFull() const override;
};

class CombB: public Function
{
public:
	CombB() {}
	virtual Type type() const override { return Type::CombB; }
	virtual unsigned maxArgs() const override { return 2; }
	virtual NodePtr evalFull() const override;
};

class CombI: public Function
{
public:
	CombI() {}
	virtual Type type() const override { return Type::CombI; }
	virtual unsigned maxArgs() const override { return 2; }
	virtual NodePtr evalFull() const override;
};

class Cons: public Function
{
public:
	Cons() {}
	virtual Type type() const override { return Type::Cons; }
	virtual unsigned maxArgs() const override { return 2; }
	virtual NodePtr evalFull() const override;
};

class Car: public Function
{
public:
	Car() {}
	virtual Type type() const override { return Type::Car; }
	virtual unsigned maxArgs() const override { return 2; }
	virtual NodePtr evalFull() const override;
};

class Cdr: public Function
{
public:
	Cdr() {}
	virtual Type type() const override { return Type::Cdr; }
	virtual unsigned maxArgs() const override { return 2; }
	virtual NodePtr evalFull() const override;
};

class IsNil: public Function
{
public:
	IsNil() {}
	virtual Type type() const override { return Type::IsNil; }
	virtual unsigned maxArgs() const override { return 2; }
	virtual NodePtr evalFull() const override;
};

#endif // FUNCTIONS_H
