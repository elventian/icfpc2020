#include "Factory.h"
#include "Functions.h"
#include "Apply.h"

const QMap<QByteArray, Type> Factory::stringToType = {
	{ "nil", Type::Nil },
	{ "inc", Type::Successor },
	{ "dec", Type::Predecessor },
	{ "add", Type::Sum },
	{ "mul", Type::Product },
	{ "div", Type::IntDivision },
	{ "eq", Type::Equality },
	{ "t", Type::True },
	{ "f", Type::False },
	{ "g", Type::Less },
	{ "mod", Type::Modulate },
	{ "dem", Type::Demodulate },
	{ "send", Type::Send },
	{ "neg", Type::Negate },
	{ "s", Type::CombS },
	{ "c", Type::CombC },
	{ "b", Type::CombB },
	{ "pwr2", Type::Power2 },
	{ "i", Type::CombI },
	{ "cons", Type::Cons },
	{ "car", Type::Car },
	{ "cdr", Type::Cdr },
	{ "isnil", Type::IsNil },
	{ "draw", Type::Draw },
	{ "checkerboard", Type::Checkerboard },
	{ "multipledraw", Type::MultipleDraw },
	{ "if0", Type::Is0 },
	{ "interact", Type::Interact },
	{ "statelessdraw", Type::StatelessDraw },
	{ "ap", Type::Apply },
};

Node *Factory::createNodeByType(Type type)
{
	switch (type) {
		case Type::Nil: { return new Nil(); }
		case Type::Product: { return new Product(); }
		case Type::IntDivision: { return new IntDivision(); }
		case Type::Equality: { return new Equality(); }
		case Type::True: { return new True(); }
		case Type::Less: { return new Less(); }
		case Type::Negate: { return new Negate(); }
		case Type::CombS: { return new CombS(); }
		case Type::CombC: { return new CombC(); }
		case Type::CombB: { return new CombB(); }
		case Type::CombI: { return new CombI(); }
		case Type::Cons: { return new Cons(); }
		case Type::Car: { return new Car(); }
		case Type::Cdr: { return new Cdr(); }
		case Type::IsNil: { return new IsNil(); }
		case Type::Apply: { return new Apply(); }

		default: return nullptr;
	}
	return nullptr;
}
