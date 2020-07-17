#include "Symbol.h"
#include "SymbolPage.h"
#include <iostream>
#include <assert.h>
#include <math.h>

QMap<int, Symbol::Type> Symbol::types;

void Symbol::init()
{
	types[0]   = Apply;
	types[1]   = Id;
	types[2]   = True;
	types[5]   = F20;
	types[6]   = Flip;
	types[7]   = F18;
	types[8]   = False;
	types[10]  = Negate;
	types[12]  = Statement;
	types[14]  = F28;
	types[40]  = IntDivision;
	types[146] = Product;
	types[170] = ToLinear;
	types[341] = ToGlyph;
	types[365] = Sum;
	types[401] = Predecessor;
	types[416] = Less;
	types[417] = Successor;
	types[448] = Equality;
	types[64170] = Cons;
	types[64171] = Cdr;
	types[64174] = Car;
}

Symbol::Symbol(const SymbolPage *page, QRect &zone)
{
	int width = 1, height = 1;
	int x = zone.left(), y = zone.top();
	m_type = Invalid;
	bool linearPositive = page->at(x, y + 1) && page->at(x + 1, y);
	bool linearNegative = page->at(x, y) && page->at(x + 1, y + 1);
	if ((linearPositive || linearNegative) && 
	!page->at(x, y + 2) && (page->at(x + 2, y) || page->at(x + 2, y + 1))) {
		//parse linear representation
		int n = 0, intWidth;
		while (page->at(x + 2 + n, y)) { n++; }
		intWidth = n * 4;
		int64_t value = 0;
		for (int i = 0; i < intWidth; i++) {
			if (page->at(x + 2 + (n + 1) + i, y)) {
				value += 1 << (intWidth - i - 1);
			}
		}
		if (linearNegative) { value *= -1; }
		*this = Symbol(value);
		height = 2;
		width = 3 + n + intWidth;
	}
	else {
		if (!(page->at(x + 1, y) && page->at(x, y + 1))) { return; }
		do { width++; } while (page->at(x + width, y));
		
		height = width;
		assert(width < 9);
		
		if (!page->at(x, y)) {
			m_type = Int;
			m_value = parseInt(page, x + 1, y + 1, width, height);
			if (page->at(x, y + height)) {
				height++;
				m_value *= -1;
			}
		}
		else {
			if (page->at(x + 1, y + 1) && width > 2) {
				m_type = Variable;
				for (int i = 1; i < width; i++) {
					if (!page->at(x + i, y + height - 1) ||
						!page->at(x + width - 1, y + i))
					{
						m_type = Invalid;
						break;
					}
				}
				for (int i = 2; i < width - 1; i++) {
					if (page->at(x + i, y + 1) ||
						page->at(x + 1, y + i)) 
					{
						m_type = Invalid;
						break;
					}
				}
			}
			if (m_type == Variable) {
				m_value = parseInt(page, x + 2, y + 2, width - 1, height - 1, true);
			}
			else {
				m_value = parseInt(page, x + 1, y + 1, width, height);
				assert(types.contains(m_value));
				m_type = types[m_value];
			}
		}
	}
	zone.setSize(QSize(width, height));
}

Symbol::Symbol(int64_t value)
{
	m_type = Int;
	m_value = value;
}

Symbol::Symbol(const QByteArray &bits, int &length, int offset)
{
	//parse linear representation
	int n = 0, intWidth;
	while (bits[offset + 2 + n]) { n++; }
	intWidth = n * 4;
	int64_t value = 0;
	for (int i = 0; i < intWidth; i++) {
		if (bits[offset + 2 + (n + 1) + i]) {
			value += 1 << (intWidth - i - 1);
		}
	}
	bool linearNegative = bits[offset + 0] && !bits[offset + 1];
	if (linearNegative) { value *= -1; }
	*this = Symbol(value);
	length = 3 + n + n * 4;
}

ByteRect Symbol::glyph() const
{
	QSize size = getGlyphSize();
	int h = size.height();
	int w = size.width();
	ByteRect arr(size, false);
	if (m_type == Variable) {
		//frame
		for (int x = 0; x < w; x++)  { arr.at(x, 0) = arr.at(x, h - 1) = true; }
		for (int y = 1; y < h - 1; y++) { arr.at(0, y) = arr.at(w - 1, y) = true; }
		generateInt(arr, 1, 1, w - 2, h - 2, true);
	}
	else {
		generateInt(arr, 0, 0, w, h);
		if (m_type != Int) { arr.at(0, 0) = true; } //top left corner
	}
	return arr;
}

ByteRect Symbol::linear() const
{
	const QByteArray &larr = linearBits();
	ByteRect res(QSize(larr.length(), 2), false);
	for (int i = 0; i < larr.length(); i++) {
		if (larr[i]) {
			res.at(i, 0) = true;
		}
		else {
			res.at(i, 1) = true;
		}
	}
	return res;
}

QByteArray Symbol::linearBits() const
{
	int64_t value = abs(m_value);
	int n = 0, width = 3;
	if (value != 0)
	{
		int intWidth = log2(value); //meaning integer part
		n = (intWidth / 4 + 1);
		width = 2 + n + 1 + n * 4;
	}
	QByteArray res(width, false);
	if (m_type == Int) {
		if (m_value >= 0) { res[1] = true;}
		else { res[0] = true; }
		for (int i = 0; i < n; i++) {
			res[2 + i] = true;
		}
		int i = width - 1;
		while (value > 0) {
			if (value & 0x1) {
				res[i] = true;
			}
			value = value >> 1;
			i--;
		}
	}
	else {
		assert(m_type == Int);
	}
	return res;
}

int64_t Symbol::parseInt(const SymbolPage *page, int x, int y, int width, int height, bool inverted)
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

void Symbol::generateInt(ByteRect &arr, int x, int y, int width, int height, bool inverted) const
{
	for (int xi = 1; xi < width; xi++)  { arr.at(x + xi, y) = !inverted; } //top frame
	for (int yi = 1; yi < height; yi++) { arr.at(x, y + yi) = !inverted; } //left frame
	uint64_t value = abs(m_value);
	int xi = 1, yi = 1;
	while (value > 0) {
		if (value & 0x1) {
			arr.at(x + xi, y + yi) = !inverted;
		}
		value = value >> 1;
		xi++;
		if (xi == width) {
			xi = 1;
			yi++;
		}
	}
	
}

QSize Symbol::getGlyphSize() const
{
	if (m_value == 0) { return QSize(2, 2); }
	int side = ceil(sqrt(log2(abs(m_value)) + 1)) + 1;
	return QSize(side, side + (m_value < 0));
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
		case Symbol::True:        stream << "a1"; break;
		case Symbol::False:       stream << "a2"; break;
		case Symbol::Less:        stream << "<"; break;
		case Symbol::ToLinear:    stream << "〜"; break;
		case Symbol::ToGlyph:     stream << "#"; break;
		case Symbol::Negate:      stream << "-"; break;
		case Symbol::F18:         stream << "a(c, b(c))"; break;
		case Symbol::Flip:        stream << "a(c, b)"; break;
		case Symbol::F20:         stream << "a(b(c))"; break;
		case Symbol::Id:          stream << "a"; break;
		case Symbol::Cons:        stream << "c(a,b)"; break;
		case Symbol::Car:         stream << "a(true)"; break;
		case Symbol::Cdr:         stream << "a(false)"; break;
		case Symbol::F28:         stream << "null"; break;
	}
	return stream;
}
