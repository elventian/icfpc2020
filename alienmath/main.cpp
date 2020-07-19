#include <iostream>
#include <gmpxx.h>
#include <QCommandLineParser>
#include <QApplication>
#include "SymbolPage.h"
#include "Symbol.h"
#include "Client.h"
#include "Interaction.h"
#include "Game.h"

int main(int argc, char* argv[]) 
{
	QApplication app(argc, argv);
	QCommandLineParser parser;
	QCommandLineOption parseImageOpt("parse-image", "Parse math from image", "path");
	QCommandLineOption fromBinary("from-bin", "Convert binary into int or list<int>", "b_str");
	QCommandLineOption connectAliens("aliens", "Send something to aliens");
	QCommandLineOption gui("run", "Run alien protocol", "file");
	parser.addHelpOption();
	parser.addOption(parseImageOpt);
	parser.addOption(fromBinary);
	parser.addOption(connectAliens);
	parser.addOption(gui);
	parser.process(app);
	
	Symbol::init();
	if (parser.isSet(gui)) {
		QString protocolFile = parser.value(gui);
		Interaction interaction(protocolFile);
		//return app.exec();
	}
	else if (parser.isSet(parseImageOpt)) {
		QString imageFile = parser.value(parseImageOpt);
		SymbolPage page = SymbolPage(QImage(imageFile));
		std::cout << page << std::endl;
	}
	else if (parser.isSet(connectAliens)) {
		//Client client;
	}
	else if (parser.isSet(fromBinary)) {
		Game game;
		std::string value = parser.value(fromBinary).toStdString();
		game.parseState(value);
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
