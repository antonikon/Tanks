#-------------------------------------------------
#
# Project created by QtCreator 2013-09-08T18:26:32
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Client
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    client.cpp \
    ../Proto/p.pb.cc \
    tank.cpp \
    buffer.cpp \
    wall.cpp \
    bullet.cpp

HEADERS  += mainwindow.h \
    client.h \
    ../Proto/p.pb.h \
    tank.h \
    buffer.h \
    wall.h \
    bullet.h

FORMS    += mainwindow.ui

LIBS += -lprotobuf

QMAKE_CXXFLAGS += -std=c++0x

OTHER_FILES += \
    ../Proto/p.proto
