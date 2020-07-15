#include "Symbol.h"
#include "SymbolPage.h"
#include <iostream>
#include <assert.h>

QMap<int, Symbol::Type> Symbol::types;

void Symbol::init()
{
	types[0]   = Apply;
	types[2]   = True;
	types[8]   = False;
	types[12]  = Statement;
	types[40]  = IntDivision;
	types[146] = Product;
	types[365] = Sum;
	types[401] = Predecessor;
	types[416] = Less;
	types[417] = Successor;
	types[448] = Equality;
}

Symbol::Symbol(const SymbolPage *page, int x, int y)
{
	m_width = 1;
	m_type = Invalid;
	if (!(page->at(x + 1, y) && page->at(x, y + 1))) { return; }
	do { m_width++; } while (page->at(x + m_width, y));
	
	m_height = m_width;
	assert(m_width < 9);
	
	if (!page->at(x, y)) {
		m_type = Int;
		m_value = parseValue(page, x + 1, y + 1, m_width, m_height);
		if (page->at(x, y + m_height)) {
			m_height++;
			m_value *= -1;
		}
	}
	else {
		m_type = Variable;
		for (int i = 1; i < m_width; i++) {
			if (!page->at(x + i, y + m_height - 1) ||
				!page->at(x + m_width - 1, y + i)) {
				m_type = Invalid;
				break;
			}
		}
		if (m_type == Variable) {
			m_value = parseValue(page, x + 2, y + 2, m_width - 1, m_height - 1, true);
		}
		else {
			m_value = parseValue(page, x + 1, y + 1, m_width, m_height);
			assert(types.contains(m_value));
			m_type = types[m_value];
		}
	}
}

int64_t Symbol::parseValue(const SymbolPage *page, int x, int y, int width, int height, bool inverted) const
{
	int64_t value = 0;
	int offset = 0;
	for (int curY = y; curY < y + width - 1; curY++)
		for (int curX = x; curX < x + height - 1; curX++)
		{
			value += (page->at(curX, curY) != inverted) << offset;
			offset++;
		}
	return value;
}

std::ostream &operator<<(std::ostream &stream, const Symbol &symbol)
{
	switch (symbol.type()) {
		case Symbol::Invalid:     stream << "�"; break;
		case Symbol::Int:         stream << symbol.value(); break;
		case Symbol::Variable:    stream << "x" << symbol.value(); break;
		case Symbol::Statement:   stream << "="; break;
		case Symbol::Apply:       stream << "␣"; break;
		case Symbol::Predecessor: stream << "--"; break;
		case Symbol::Successor:   stream << "++"; break;
		case Symbol::Sum:         stream << "+"; break;
		case Symbol::Product:     stream << "⨯"; break;
		case Symbol::IntDivision: stream << "/"; break;
		case Symbol::Equality:    stream << "=="; break;
		case Symbol::True:        stream << "t"; break;
		case Symbol::False:       stream << "f"; break;
		case Symbol::Less:        stream << "<"; break;
	}
	return stream;
}
