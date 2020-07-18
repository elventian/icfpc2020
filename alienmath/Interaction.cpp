#include "Interaction.h"
#include "Apply.h"
#include "Environment.h"
#include "List.h"


Interaction::Interaction(const QString &protocolFile)
{
	Environment env(protocolFile);
	//ap ap protocol nil ap ap cons 1 2
	Apply *root = 
		new Apply(
			new Apply(env.getTree(), NodePtr(new Nil())),
			new Apply(
				new Apply(new Cons(), new Int(1)), 
				new Int(2)));
	List list(root->eval());
}
