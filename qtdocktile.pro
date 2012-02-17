QTDOCKTILE_VERSION = 1.0.0
TEMPLATE = subdirs
CONFIG += ordered
SUBDIRS += \
    examples\
    src

OTHER_FILES += \
    doc/qtdocktile.qdoc

include(doc/doc.pri)
 
