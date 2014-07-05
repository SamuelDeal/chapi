TEMPLATE = app
CONFIG += console static c++-11
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra

target.path = /usr/bin/chapi
INSTALLS += target

SOURCES += src/main.cpp \
    src/helloer.cpp \
    src/networkconfig.cpp \
    src/etime.cpp \
    src/nlprotocol.cpp \
    src/config.cpp \
    src/systemutils.cpp \
    src/log.cpp \
    src/videohub.cpp \
    src/server.cpp \
    src/servercnx.cpp \
    src/chapi.cpp

HEADERS += \
    src/helloer.h \
    src/const.h \
    src/networkconfig.h \
    src/etime.h \
    src/nlprotocol.h \
    src/config.h \
    src/stringutils.h \
    src/systemutils.h \
    src/log.h \
    src/videohub.h \
    src/server.h \
    src/servercnx.h \
    src/chapi.h

