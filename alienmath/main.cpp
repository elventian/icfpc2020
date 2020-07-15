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
	
	return 0;
}
