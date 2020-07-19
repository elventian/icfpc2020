CONFIG +=  c++11
CONFIG -= app_bundle
QT -= gui core

SOURCES += \ 
    main.cpp \
    Game.cpp \
    GameState.cpp

HEADERS += \ 
    Game.h \
    GameState.h

INCLUDEPATH +=

LIBS += -lgmpxx -lgmp 
