#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "ParsedNode.h"
#include <QString>
#include <QMap>
#include <QStack>

class Apply;

class Environment
{
public:
	Environment(const QString &filename);
	static Node *createNodeByType(Type type);

private:
	typedef QMap<ParsedNode::Id, NodePtr> NodeMap;

	static ParsedNode::Id parseFuncId(const QByteArray &token);
	NodePtr createTreeFromTokens(const QList<QByteArray> &tokens);
	const NodePtr &getOrCreateParsedNode(ParsedNode::Id id);
	void addNode(const NodePtr &newNode);

	NodeMap m_parsedNodes;
	NodePtr m_root;

	NodePtr m_curRoot;
	QStack<const Apply *> m_applyStack;
};

#endif // ENVIRONMENT_H
