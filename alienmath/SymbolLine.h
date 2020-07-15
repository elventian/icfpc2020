#ifndef SYMBOLLINE_H
#define SYMBOLLINE_H

#include "Symbol.h"
#include <QLinkedList>
#include <iostream>

class SymbolLine
{
public:
	friend std::ostream &operator<<(std::ostream &stream, const SymbolLine &line);
	
	SymbolLine &operator<<(const Symbol &s) {
		m_symbols << s;
		return *this;
	}
private:
	QLinkedList<Symbol> m_symbols;
};

#endif // SYMBOLLINE_H
