#ifndef CONSINT_H
#define CONSINT_H

#include "ConsNode.h"
#include <stdint.h>

class ConsInt: public ConsNode
{
public:
	ConsInt(int64_t value): m_value(value) {}
	virtual Type type() const override { return Type::Int; }
	virtual std::string printable() const override { return std::to_string(m_value); }
	int64_t value() const { return m_value; }

private:
	const int64_t m_value;
};

#endif // CONSINT_H
