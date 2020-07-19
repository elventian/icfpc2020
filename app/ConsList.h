#ifndef CONSLIST_H
#define CONSLIST_H

#include "ConsNode.h"
#include <vector>

class ConsList: public ConsNode, public std::vector<ConsNodePtr>
{
public:
	ConsList(const std::string &linear, const char **linPtrPtr = nullptr);
	virtual Type type() const override { return m_vector2? Type::Vector2 : Type::List; }
	virtual std::string printable() const override;
	bool isValid() const { return m_valid; }

private:
	static std::string two(const char *linear) { return std::string(linear, 2); }

	bool m_valid = true;
	bool m_vector2 = false;
};

#endif // CONSLIST_H
