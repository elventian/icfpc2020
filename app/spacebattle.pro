CONFIG +=  c++11
CONFIG -= app_bundle
QT -= gui core

SOURCES += \ 
    main.cpp \
    Game.cpp

HEADERS += \ 
    Game.h

INCLUDEPATH +=

LIBS += -lgmpxx -lgmp 
