#-------------------------------------------------
#
# Project created by QtCreator 2013-09-08T18:26:51
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = Server
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    server.cpp \
    ../Proto/p.pb.cc \
    player.cpp \
    world.cpp \
    tank.cpp \
    wall.cpp \
    bullet.cpp

LIBS += -lprotobuf

QMAKE_CXXFLAGS += -std=c++0x

HEADERS += \
    server.h \
    ../Proto/p.pb.h \
    player.h \
    world.h \
    tank.h \
    wall.h \
    bullet.h

OTHER_FILES += \
    ../Proto/p.proto
