if(USE_QT5)
    set(_extra_qt Quick)
else()
    set(_extra_qt Declarative)
endif()

add_qml_module(qmldocktileplugin
    URI org.docktile
    QML_DIR qmldir
    SOURCE_DIR src
    LIBRARIES qtdocktile ${QT_QTDECLARATIVE_LIBRARY}
    INCLUDES ../../lib ${QT_QTDECLARATIVE_INCLUDE_DIR}
    IMPORTS_DIR ${QT_QTDOCKTILE_IMPORTS_DIR}
    QT Core Gui Widgets ${_extra_qt}
)
