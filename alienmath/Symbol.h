#ifndef SYMBOL_H
#define SYMBOL_H

#include <cstdint>
#include <iostream>
#include <QMap>

class SymbolPage;

class Symbol
{
public:
	friend std::ostream &operator<<(std::ostream &stream, const Symbol &symbol);
	
	enum Type {	Invalid, 
		Int, Variable, Statement, True, False, Apply, 
		Successor, Predecessor, Sum, Product, IntDivision, 
		Equality, Less };
	
	static void init();
	Symbol(const SymbolPage *page, int x, int y);
	
	int width() const { return m_width; }
	int height() const { return m_height; }
	Type type() const { return m_type; }
	int64_t value() const { return m_value; }
	
private:
	int m_width;
	int m_height;
	Type m_type;	
	int64_t m_value;
	static QMap<int, Type> types;
	
	int64_t parseValue(const SymbolPage *page, int x, int y, 
		int width, int height, bool inverted = false) const;
};


#endif // SYMBOL_H
