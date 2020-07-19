#include "ConsList.h"
#include "ConsInt.h"
#include "Game.h"

ConsList::ConsList(const std::string &linear, const char **linPtrPtr)
{
	const char *linPtr;
	if (!linPtrPtr) {
		linPtr = linear.c_str();
		linPtrPtr = &linPtr;
		if (two(*linPtrPtr) != "11") { m_valid = false; return; }
	}

	bool rightPart = true;
	while (*linPtrPtr) {
		const std::string head = two(*linPtrPtr);
		if (head == "11") { // cons
			if (rightPart) { // Regular list from chained cons.
				(*linPtrPtr) += 2;
			}
			else { // New list.
				push_back(ConsNodePtr(new ConsList(linear, linPtrPtr)));
			}
		}
		else if (head == "00") { // nil
			(*linPtrPtr) += 2;
			if (rightPart) { return; }
		}
		else { // int
			int bits = 0;
			const int64_t intVal = Game::intFromLinear(*linPtrPtr, bits);
			(*linPtrPtr) += bits;
			push_back(ConsNodePtr(new ConsInt(intVal)));
			if (rightPart) {
				m_vector2 = true;
				return;
			}
		}

		rightPart = !rightPart;
	}
}

std::string ConsList::printable() const
{
	std::string str = isVector2()? "{" : "[";
	bool started = false;
	for (const ConsNodePtr &child: *this) {
		if (started) { str += ','; }
		started = true;
		str += child->printable();
	}
	str += isVector2()? "}" : "]";
	return str;
}
