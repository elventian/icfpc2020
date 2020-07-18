#include "Apply.h"
#include <assert.h>

void Apply::determineApType() const
{
	assert(m_left != nullptr);

	switch (m_left->type()) {
		case Type::Apply: {
			const Apply *childApply = dynamic_cast<const Apply *>(m_left.get());
			childApply->determineApType(); // Recursive call.
			switch (childApply->m_apType) {
				case ApType::HalfPair: { m_apType = ApType::Pair; break; }
				default: { m_apType = ApType::Any; }
			}
			break;
		}
		case Type::Cons: { m_apType = ApType::HalfPair; break; }
		default: { m_apType = ApType::Any; }
	}
}

NodePtr Apply::eval() const
{
	assert(m_left != nullptr);
	assert(m_right != nullptr);

	return m_left->pass(m_right);
}

NodePtr Apply::pass(const NodePtr &arg) const
{
	assert(m_left != nullptr);
	assert(m_right != nullptr);

	NodePtr newNode = m_left->pass(m_right);
	return newNode->pass(arg);
}
