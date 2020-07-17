TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += qt

SOURCES += \ 
    main.cpp \
    SymbolPage.cpp \
    Symbol.cpp \
    SymbolLine.cpp \
    Client.cpp

HEADERS += \ 
    SymbolPage.h \
    Symbol.h \
    SymbolLine.h \
    ByteRect.h \
    Client.h

INCLUDEPATH +=

LIBS += -lgmpxx -lgmp 
