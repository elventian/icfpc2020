#ifndef SYMBOL_H
#define SYMBOL_H

#include <cstdint>
#include <iostream>
#include <QMap>
#include <QRect>
#include "ByteRect.h"

class SymbolPage;

class Symbol
{
public:
	friend std::ostream &operator<<(std::ostream &stream, const Symbol &symbol);
	
	enum Type {	Invalid, 
		Int, Variable, Statement, True, False, Negate, Apply, 
		Successor, Predecessor, Sum, Product, IntDivision,
		ToLinear, ToGlyph,
		Equality, Less,
		F18, Flip, F20, Id, Cons, Car, Cdr, F28};
	
	static void init();
	
	Symbol(int64_t value);
	Symbol(const QByteArray &bits, int &length, int offset = 0);
	
	//parse Symbol from page starting from zone top left corner; 
	//fill zone with width and height of parsed symbol
	Symbol(const SymbolPage *page, QRect &zone); 
	
	Type type() const { return m_type; }
	int64_t value() const { return m_value; }
	ByteRect glyph() const; //generate glyph (2d)
	ByteRect linear() const; //generate linear representation
	QByteArray linearBits() const;
	
private:
	Type m_type;	
	int64_t m_value;
	static QMap<int, Type> types;
	
	Symbol() {}
	static int64_t parseInt(const SymbolPage *page, int x, int y, 
		int width, int height, bool inverted = false);
	void generateInt(ByteRect &arr, int x, int y, 
		int width, int height, bool inverted = false) const;
	QSize getGlyphSize() const;
};


#endif // SYMBOL_H
