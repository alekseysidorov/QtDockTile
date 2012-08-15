if(QT_QTDOCKTILE_WITH_QMLAPI)
    add_subdirectory(imports)
endif()
if(NOT QT_QTDOCKTILE_INSTALL_HEADERS)
    set(QT_DOCKTILE_INTERNAL_FLAG "INTERNAL")
endif()

add_subdirectory(lib) 
add_subdirectory(plugins) 
