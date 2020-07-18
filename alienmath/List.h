#ifndef LIST_H
#define LIST_H

#include <QVariant>
#include "Node.h"

class List
{
public:
	List(const NodePtr &tree);
	
private:
	QVariant parseTree(const NodePtr &tree) const;
	
	QVariant m_data;
};

#endif // LIST_H
