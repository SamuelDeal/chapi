TEMPLATE = app
CONFIG += console static c++-11
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra

SOURCES += main.cpp \
    helloer.cpp \
    networkconfig.cpp \
    etime.cpp \
    nlprotocol.cpp \
    config.cpp \
    systemutils.cpp \
    log.cpp \
    videohub.cpp \
    server.cpp \
    servercnx.cpp \
    chapi.cpp

HEADERS += \
    helloer.h \
    const.h \
    networkconfig.h \
    etime.h \
    nlprotocol.h \
    config.h \
    stringutils.h \
    systemutils.h \
    log.h \
    videohub.h \
    server.h \
    servercnx.h \
    chapi.h

