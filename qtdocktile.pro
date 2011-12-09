#-------------------------------------------------
#
# Project created by QtCreator 2011-11-27T17:33:04
#
#-------------------------------------------------

TARGET = QtDockIcon
TEMPLATE = lib

DEFINES += QTDOCKTILE_LIBRARY

SOURCES += \
    qtdocktile.cpp \
    qtdockprovider.cpp \
    qtdockmanager.cpp

HEADERS += \
    qtdocktile.h \
    qtdocktile_global.h \
    qtdocktile_p.h \
    qtdockprovider.h \
    qtdockmanager_p.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

include(plugins/plugins.pri)














