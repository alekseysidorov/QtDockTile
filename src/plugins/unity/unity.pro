DESTDIR= ../../../../plugins/docktile
TEMPLATE = lib
TARGET = unitylauncher
DEPENDPATH += .
INCLUDEPATH += .

QT = core dbus

unix: CONFIG += plugin

HEADERS += unitylauncher.h
SOURCES += unitylauncher.cpp

