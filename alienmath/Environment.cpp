#include "Environment.h"
#include "Apply.h"
#include "Factory.h"
#include <stdlib.h>
#include <QFile>
#include <QTextStream>

static const QByteArray rootName = "galaxy";

Environment::Environment(const QString& filename)
{
	QFile file(filename);
	if (!file.exists()) {
		QTextStream(stderr) << "File " << filename << " does not exist." << endl;
		exit(1);
	}

	if (!file.open(QIODevice::ReadOnly)) {
		QTextStream(stderr) << "File " << filename << " could not be opened for reading." << endl;
		exit(1);
	}

	const QByteArray ba = file.readAll();
	QList<QByteArray> lines = ba.split('\n');

	// Create nodes of type ParsedNode for every line.
	for (const QByteArray &line: lines) {
		const QList<QByteArray> assignmentSides = line.split('=');
		const QByteArray idStr = assignmentSides[0].trimmed();
		const QByteArray valStr = assignmentSides[1].trimmed();
		if (idStr == rootName) {
			const ParsedNode::Id id = parseFuncId(valStr);
			const NodeMap::iterator iter = m_parsedNodes.find(id);
			if (iter == m_parsedNodes.end()) {
				QTextStream(stderr) << "Node " << rootName << " defined before its value." << endl;
				exit(1);
			}
			m_root = iter.value();
			continue;
		}

		const ParsedNode::Id id = parseFuncId(idStr);

		// If ParsedNode with the id was not created by referencing yet, then create it now.
		NodeMap::iterator iter = m_parsedNodes.find(id);
		if (iter == m_parsedNodes.end()) {
			iter = m_parsedNodes.insert(id, NodePtr(new ParsedNode(id)));
		}

		const NodePtr &parsedNode = getOrCreateParsedNode(id);

		// Create real node from line, and assign to ParsedNode.
		dynamic_cast<const ParsedNode *>(parsedNode.get())->setNode(
			createTreeFromTokens(valStr.split(' ')));
	}
}

NodePtr Environment::createTreeFromTokens(const QList<QByteArray> &tokens)
{
	m_curRoot = nullptr;
	m_applyStack.clear();

	for (const QByteArray &token: tokens) {
		if (token.startsWith(':')) {
			const ParsedNode::Id id = parseFuncId(token);
			addNode(getOrCreateParsedNode(id));
			continue;
		}

		const auto typeIter = Factory::stringToType.find(token);
		if (typeIter != Factory::stringToType.end()) {
			const Type type = typeIter.value();
			Node *node = Factory::createNodeByType(type);
			if (!node) {
				QTextStream(stderr) << "Can't create object for type \"" << token << "\"" << endl;
				exit(1);
			}
			addNode(NodePtr(node));
			continue;
		}

		bool ok;
		int64_t intVal = token.toLongLong(&ok);
		if (!ok) {
			QTextStream(stderr) << "Unknown token \"" << token << "\"" << endl;
			exit(1);
		}
		addNode(NodePtr(static_cast<const Node *>(new Int(intVal))));
	}

	return *m_curRoot;
}

const NodePtr &Environment::getOrCreateParsedNode(ParsedNode::Id id)
{
	NodeMap::iterator iter = m_parsedNodes.find(id);
	if (iter == m_parsedNodes.end()) {
		iter = m_parsedNodes.insert(id, NodePtr(new ParsedNode(id)));
	}
	return iter.value();
}

void Environment::addNode(const NodePtr &newNode)
{
	if (!m_curRoot) { m_curRoot = &newNode; }

	if (newNode->type() != Type::Apply && m_applyStack.isEmpty()) { return; }

	if (!m_applyStack.isEmpty()) {
		m_applyStack.top()->addChild(newNode);
		if (m_applyStack.top()->hasBothChildren()) {
			m_applyStack.pop();
		}
	}

	if (newNode->type() == Type::Apply) {
		m_applyStack.push(dynamic_cast<const Apply *>(newNode.get()));
	}
}

ParsedNode::Id Environment::parseFuncId(const QByteArray &token)
{
	if (!token.startsWith(':')) {
		QTextStream(stderr) << "Token \"" << token << "\" does not start from \":\"." << endl;
		exit(1);
	}

	bool ok;
	const ParsedNode::Id id = token.mid(1).toInt(&ok);
	if (!ok) {
		QTextStream(stderr) << "Token \"" << token << "\" is not int." << endl;
		exit(1);
	}
	return id;
}
