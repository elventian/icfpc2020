#ifndef CONSTREE_H
#define CONSTREE_H

#include "ConsNode.h"

class ConsTree
{
public:
	ConsTree(const std::string &linear);
	ConsNodePtr root() const { return m_root; }

private:
	ConsNodePtr m_root;
};

#endif // CONSTREE_H
