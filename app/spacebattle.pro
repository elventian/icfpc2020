CONFIG +=  c++11
CONFIG -= app_bundle
QT -= gui core

SOURCES += \ 
    main.cpp \
    Game.cpp \
    GameState.cpp \
    Commands.cpp

HEADERS += \ 
    Game.h \
    GameState.h \
    Commands.h

INCLUDEPATH +=

LIBS += -lgmpxx -lgmp 
