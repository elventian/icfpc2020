#include <iostream>
#include <gmpxx.h>
#include <QCommandLineParser>
#include "SymbolPage.h"
#include "Symbol.h"

int main(int argc, char* argv[]) 
{
	QCoreApplication app(argc, argv);
	QCommandLineParser parser;
	QCommandLineOption parseImageOpt("parse-image", "Parse math from image", "path");
	parser.addHelpOption();
	parser.addOption(parseImageOpt);
	parser.process(app);
	
	Symbol::init();
	if (parser.isSet(parseImageOpt)) {
		QString imageFile = parser.value(parseImageOpt);
		SymbolPage page = SymbolPage(QImage(imageFile));
		std::cout << page << std::endl;
	}
	else {
		while (true) {
			std::cout << "Enter number to generate 2d glyph:" << std::endl;
			int64_t value;
			std::cin >> value;
			Symbol symbol(value);
			std::cout << symbol.glyph().pseudographics(true) << std::endl;
			std::cout << symbol.linear().pseudographics(true) << std::endl;
		}
	}
	
	return 0;
}
