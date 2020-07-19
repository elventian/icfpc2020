#include "ConsNode.h"
#include "ConsInt.h"
#include "ConsList.h"

int64_t ConsNode::intVal() const
{
	const ConsInt *consInt = dynamic_cast<const ConsInt *>(this);
	if (!consInt) { return 0; }
	return consInt->value();
}

ConsList *ConsNode::asList()
{
	return dynamic_cast<ConsList *>(this);
}
