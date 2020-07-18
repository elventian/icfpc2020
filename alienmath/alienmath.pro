TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += qt

SOURCES += \ 
    main.cpp \
    SymbolPage.cpp \
    Symbol.cpp \
    SymbolLine.cpp \
    Client.cpp \
    Node.cpp \
    Type.cpp \
    Function.cpp \
    Environment.cpp \
    RuntimeFunc.cpp \
    Functions.cpp \
    Apply.cpp

HEADERS += \ 
    SymbolPage.h \
    Symbol.h \
    SymbolLine.h \
    ByteRect.h \
    Client.h \
    Node.h \
    Type.h \
    Function.h \
    Environment.h \
    RuntimeFunc.h \
    Functions.h \
    Apply.h

INCLUDEPATH +=

LIBS += -lgmpxx -lgmp 
