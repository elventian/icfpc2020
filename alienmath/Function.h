#ifndef FUNCTION_H
#define FUNCTION_H

#include "Node.h"

#include <vector>

typedef std::vector<NodePtr *> Args;

class Function: public Node
{
public:
	virtual unsigned maxArgs() const = 0;

	virtual NodePtr calculate() const override
	{
		if (m_args.size() != maxArgs()) { return thisAsNodePtr(); }
		// TODO: Call calculate() recursively for all arguments.
		return calcFull();
	}

protected:
	Function(const Args &args): m_args(args) {}

	virtual NodePtr calcFull() const = 0;

	const Args m_args;
};

#endif // FUNCTION_H
