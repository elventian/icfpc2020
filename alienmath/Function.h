#ifndef FUNCTION_H
#define FUNCTION_H

#include "Node.h"

#include <vector>
#include <assert.h>

typedef std::vector<NodePtr> Args;

class Function: public Node
{
public:
	virtual unsigned maxArgs() const = 0;
	virtual NodePtr evalFull() const = 0;

	virtual NodePtr eval() const override { assert(false); return nullptr; }
	virtual NodePtr pass(const NodePtr &arg) const override;

protected:
	Function() {}
	Function(const Args &args): m_args(args) {}
	bool hasEnoughArgs() const { return m_args.size() == maxArgs(); }

	virtual Function *clone(const Args &args) const = 0;

	const Args m_args;
};

#endif // FUNCTION_H
