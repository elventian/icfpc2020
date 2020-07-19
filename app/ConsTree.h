#ifndef CONSTREE_H
#define CONSTREE_H

#include "ConsList.h"
#include "ConsInt.h"

class ConsTree
{
public:
	ConsTree(const std::string &linear);
	ConsNodePtr root() const { return m_root; }

private:
	ConsNodePtr m_root;
};

#endif // CONSTREE_H
