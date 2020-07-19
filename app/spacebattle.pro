CONFIG +=  c++11
CONFIG -= app_bundle
QT -= gui core

SOURCES += \ 
    main.cpp \
    Game.cpp \
    GameState.cpp \
    Commands.cpp \
    DiscrCoord2.cpp \
    ConsNode.cpp \
    ConsTree.cpp \
    ConsInt.cpp \
    ConsList.cpp

HEADERS += \ 
    Game.h \
    GameState.h \
    Commands.h \
    DiscrCoord2.h \
    ConsNode.h \
    ConsTree.h \
    ConsInt.h \
    ConsList.h

INCLUDEPATH +=

LIBS += -lgmpxx -lgmp 
