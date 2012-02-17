include(modules/qt_docktile.pri)

TEMPLATE = subdirs
CONFIG += ordered
SUBDIRS += \
    examples\
    src

OTHER_FILES += \
    doc/qtdocktile.qdoc \
    sync.profile

include(doc/doc.pri)
 
