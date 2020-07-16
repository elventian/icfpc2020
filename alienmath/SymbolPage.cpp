#include "SymbolPage.h"
#include "SymbolLine.h"
#include "Symbol.h"
#include <QDebug>
#include <iostream>

std::ostream &operator<<(std::ostream &stream, const SymbolPage &page)
{
	for (SymbolLine *line: page.m_lines) {
		stream << *line << std::endl;
	}
	return stream;
}

SymbolPage::SymbolPage(const QByteArray &arr, int lineWidth) : m_arr(arr), m_lineWidth(lineWidth) 
{
	parse();
}

SymbolPage::SymbolPage(const QImage &image)
{
	int scaleFactor = 4;
	QImage withoutBorder = image.copy(scaleFactor, scaleFactor, 
		image.width() - 2 * scaleFactor,  image.height() - 2 * scaleFactor);
	m_lineWidth = withoutBorder.width() / scaleFactor;
	m_arr = QByteArray();
	for (int y = 0; y < withoutBorder.height()/scaleFactor; y++) {
		for (int x = 0; x < withoutBorder.width()/scaleFactor; x++) {
			bool white = withoutBorder.pixelColor(x * scaleFactor, y * scaleFactor) == Qt::white;
			m_arr.append(white);
			std::cout << (white ? "x" : " ");
		}
		std::cout << std::endl;
	}
	parse();
	
}

void SymbolPage::parse()
{
	int height = m_arr.length() / m_lineWidth;
	for (int y = 0; y < height - 1; y++) {
		int lineHeight = 0;
		SymbolLine *line = nullptr;
		for (int x = 0; x < m_lineWidth - 1; x++) {
			QRect zone(x, y, 0, 0);
			Symbol symbol = Symbol(this, zone);
			if (symbol.type() != Symbol::Invalid) {
				if (!line) {
					line = new SymbolLine();
					m_lines << line;
				}
				*line << symbol;
				x += zone.width();
				lineHeight = std::max(lineHeight, zone.height());
			}
		}
		y += lineHeight;
	}
}
