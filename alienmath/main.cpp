#include <iostream>
#include <gmpxx.h>
#include <QCommandLineParser>
#include "SymbolPage.h"
#include "Symbol.h"
#include "Client.h"

int main(int argc, char* argv[]) 
{
	QCoreApplication app(argc, argv);
	QCommandLineParser parser;
	QCommandLineOption parseImageOpt("parse-image", "Parse math from image", "path");
	QCommandLineOption fromBinary("from-bin", "Convert binary into 2d glyph");
	QCommandLineOption connectAliens("aliens", "Send something to aliens");
	parser.addHelpOption();
	parser.addOption(parseImageOpt);
	parser.addOption(fromBinary);
	parser.addOption(connectAliens);
	parser.process(app);
	
	Symbol::init();
	if (parser.isSet(parseImageOpt)) {
		QString imageFile = parser.value(parseImageOpt);
		SymbolPage page = SymbolPage(QImage(imageFile));
		std::cout << page << std::endl;
	}
	else if (parser.isSet(connectAliens)) {
		Client client("https://icfpc2020-api.testkontur.ru/scoreboard/lightning:80", 
			"b4c1d7d8042e46c7a5e59574839f41b9");
	}
	else if (parser.isSet(fromBinary)) {
		while (true) {
			std::cout << "Enter binary to generate 2d glyph:" << std::endl;
			std::string value;
			std::cin >> value;
			QByteArray bits = QByteArray::fromStdString(value);
			for (int i = 0; i < bits.length(); i++) {
				bits[i] = (bits[i] == '0' ? 0: 1);
			}
			Symbol symbol(bits);
			std::cout << symbol.value() << std::endl;
		}
	}
	else {
		while (true) {
			std::cout << "Enter number to generate 2d glyph:" << std::endl;
			int64_t value;
			std::cin >> value;
			Symbol symbol(value);
			std::cout << symbol.glyph().pseudographics(true) << std::endl;
			std::cout << symbol.linear().pseudographics(true) << std::endl;
			QByteArray bits = symbol.linearBits();
			for (int i = 0; i < bits.length(); i++) {
				std::cout << (bits.at(i) ? "1" : "0");
			}
			std::cout << std::endl;
		}
	}
	
	return 0;
}
