#include "Node.h"

const NodePtr Nil::sharedNil(static_cast<const Node *>(new Nil()));
