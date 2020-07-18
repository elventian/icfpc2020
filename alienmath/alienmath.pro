TEMPLATE = app
CONFIG += c++11
CONFIG -= app_bundle
CONFIG += qt
QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

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
    Functions.cpp \
    Apply.cpp \
    Factory.cpp \
    ParsedNode.cpp \
    Interaction.cpp \
    List.cpp

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
    Functions.h \
    Apply.h \
    Factory.h \
    ParsedNode.h \
    Interaction.h \
    List.h

INCLUDEPATH +=

LIBS += -lgmpxx -lgmp 
