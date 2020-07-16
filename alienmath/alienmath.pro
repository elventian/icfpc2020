TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += qt

SOURCES += \ 
    main.cpp \
    SymbolPage.cpp \
    Symbol.cpp \
    SymbolLine.cpp

HEADERS += \ 
    SymbolPage.h \
    Symbol.h \
    SymbolLine.h \
    ByteRect.h

INCLUDEPATH +=

LIBS += -lgmpxx -lgmp 
