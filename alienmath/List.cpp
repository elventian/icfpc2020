#include "List.h"
#include "Functions.h"
#include "Apply.h"
#include <QDebug>

List::List(const NodePtr &tree)
{
	m_data = parseTree(tree);
	qDebug() << m_data;
}

QVariant List::parseTree(const NodePtr &tree) const
{
	if (tree->type() == Type::Int) { return qlonglong(INT(tree)); }
	
	QVariantList list;
	const NodePtr *head = &tree;
	while (head->get()->type() != Type::Nil) {
		const Apply *headAp = APPLY(*head);
		assert(headAp);
		const Apply *consAp = APPLY(headAp->getLeft());
		assert(consAp);
		assert(consAp->getLeft()->type() == Type::Cons);
		list.push_back(parseTree(consAp->getRight()));
		head = &headAp->getRight();
	}
	return list;
}
