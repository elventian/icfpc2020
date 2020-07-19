CONFIG +=  c++11
CONFIG -= app_bundle
QT -= gui core

SOURCES += \ 
    main.cpp \
    Game.cpp \
    GameState.cpp \
    Commands.cpp \
    DiscrCoord2.cpp

HEADERS += \ 
    Game.h \
    GameState.h \
    Commands.h \
    DiscrCoord2.h

INCLUDEPATH +=

LIBS += -lgmpxx -lgmp 
