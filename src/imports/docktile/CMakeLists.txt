add_qml_module(docktile
    URI org.docktile
    QML_DIR qmldir
    SOURCE_DIR src
    LIBRARIES qtdocktile ${QT_QTDECLARATIVE_LIBRARY}
    INCLUDES ../../lib ${QT_QTDECLARATIVE_INCLUDE_DIR}
    IMPORTS_DIR ${QT_QTDOCKTILE_IMPORTS_DIR}
)
