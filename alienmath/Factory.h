#ifndef FACTORY_H
#define FACTORY_H

#include "Type.h"
#include <QMap>

class Node;

class Factory
{
public:
	static const QMap<QByteArray, Type> stringToType;
	static Node *createNodeByType(Type type);
};

#endif // FACTORY_H
