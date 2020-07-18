#include "Function.h"

NodePtr Function::pass(const NodePtr &arg) const
{
	assert(!hasEnoughArgs());

	Args newArgs(m_args);
	newArgs.push_back(arg);
	Function *newClone = clone(newArgs);

	if (newClone->hasEnoughArgs()) { return newClone->evalFull(); }
	return NodePtr(static_cast<const Node *>(newClone));
}
