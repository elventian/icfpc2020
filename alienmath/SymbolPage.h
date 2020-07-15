#ifndef SYMBOLPAGE_H
#define SYMBOLPAGE_H

#include <QByteArray>
#include <QImage>
#include <QLinkedList>

class SymbolLine;

class SymbolPage 
{
public:
	friend std::ostream &operator<<(std::ostream &stream, const SymbolPage &page);
	
	SymbolPage(const QByteArray &arr, int lineWidth);
	SymbolPage(const QImage &image);
	bool at(int x, int y) const { return m_arr[x + y * m_lineWidth]; }
private:
	QByteArray m_arr;
	QLinkedList<SymbolLine *> m_lines;
	int m_lineWidth;
	void parse();
};

#endif // SYMBOLPAGE_H
