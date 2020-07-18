#ifndef RUNTIMEFUNC_H
#define RUNTIMEFUNC_H

#include "Function.h"

class RuntimeFunc : public Function
{
public:
	typedef int Id;

	RuntimeFunc(Id id): Function(Args()), m_id(id) {}
	void setNode(const Function *node) { m_node = node; }

	virtual Type type() const override { return m_node->type(); }

protected:
	virtual unsigned maxArgs() const override { return m_node->maxArgs(); }
	virtual NodePtr calcFull() const override { return m_node->calculate(); }

private:
	Id m_id;
	const Function *m_node = nullptr;
};

#endif // RUNTIMEFUNC_H
