#include "Interaction.h"
#include "Apply.h"

/*ap ap ap interact x2 x4 x3 = ap ap f38 x2 ap ap x2 x4 x3*/
NodePtr Interact::evalFull() const
{
	const NodePtr &protocol = m_args[0];
	const NodePtr &state = m_args[1];
	const NodePtr &vector = m_args[2];
	
	NodePtr f38 = NODE(new F38());
	
	return f38->pass(protocol)->pass(protocol->pass(state)->pass(vector));
}


//stateList - list of (flag, newState, data)
NodePtr F38::evalFull() const
{
	/*const NodePtr &protocol = m_args[0];
	const NodePtr &stateList = m_args[1];
	
	const NodePtr &is0 = NODE(new Is0());
	const NodePtr &car = NODE(new Car());
	const NodePtr &cdr = NODE(new Cdr());
	
	Apply *drawApply = new Apply();
	drawApply->setLeft();
	const NodePtr &drawNode = NODE(new Apply());
	
	car->pass(stateList);*/
	//is0->pass()
}

NodePtr Draw::evalFull() const {
	const NodePtr &pixels = m_args[0];
	//TODO
}

