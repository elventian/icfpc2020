TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += qt
QT += core

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += \ 
    main.cpp \
    Game.cpp

HEADERS += \ 
    Game.h

INCLUDEPATH +=

LIBS += -lgmpxx -lgmp 
