#include "SymbolLine.h"

std::ostream &operator<<(std::ostream &stream, const SymbolLine &line)
{
	for (const Symbol &s: line.m_symbols) {
		stream << s << ' ';
	}
	return stream;
}
