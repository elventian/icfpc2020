#include "ConsTree.h"
#include "Game.h"

ConsTree::ConsTree(const std::string &linear)
{
	ConsList *list = new ConsList(linear);
	if (list->isValid()) {
		m_root = ConsNodePtr(static_cast<ConsNode *>(list));
		return;
	}

	delete list;
	int64_t intVal = Game::intFromLinear(linear);
	m_root = ConsNodePtr(static_cast<ConsNode *>(new ConsInt(intVal)));
}
