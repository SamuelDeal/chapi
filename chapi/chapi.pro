TEMPLATE = app
CONFIG += console static c++-11
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -lrt -lpthread
DEFINES += "NOGPIO=0"
INCLUDEPATH += ../common/src
LIBS += -pthread 
LIBS += -L../common -lcommon -lrt

target.path = /usr/bin/chapi
INSTALLS += target

SOURCES += src/main.cpp


