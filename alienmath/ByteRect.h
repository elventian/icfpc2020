#ifndef BYTERECT_H
#define BYTERECT_H

#include <QByteArray>
#include <QSize>

class ByteRect: public QByteArray
{
public:
	ByteRect(QSize size, bool fillWithValue):
		QByteArray(size.width() * size.height(), fillWithValue), m_size(size) {}
	
	QByteRef at(int x, int y) {
		return QByteArray::operator[](x + y * m_size.width());
	}
	
	char at(int x, int y) const {
		return QByteArray::operator[](x + y * m_size.width());
	}
	
	std::string pseudographics(bool addOuterBorder) const
	{
		int width = m_size.width(), height = m_size.height();
		std::string res;
		std::string borderSymbol = "⬛";
		if (addOuterBorder) {
			for (int x = 0; x < width + 2; x++) { res += borderSymbol; }
			res += "\n";
		}
		for (int y = 0; y < height; y++) {
			if (addOuterBorder) { res += borderSymbol; }
			for (int x = 0; x < width; x++) {
				res += (at(x, y) ? "⬜" : "⬛"); 
			}
			if (addOuterBorder) { res += borderSymbol; }
			res += "\n";
		}
		if (addOuterBorder) {
			for (int x = 0; x < width + 2; x++) { res += borderSymbol; }
			res += "\n";
		}
		return res;
	}
	
private:
	QSize m_size;
};

#endif // BYTERECT_H
