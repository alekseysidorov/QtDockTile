#-------------------------------------------------
#
# Project created by QtCreator 2011-12-09T19:13:31
#
#-------------------------------------------------

QT       += core gui

TARGET = MacDockTile
TEMPLATE = lib
CONFIG += plugin

SOURCES += \
    macdocktile.mm
HEADERS += macdocktile.h

INCLUDEPATH += ../../

macx: QMAKE_LFLAGS += -framework Cocoa
