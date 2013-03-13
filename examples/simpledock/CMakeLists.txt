project(simpledock)

if(NOT QT_QTDOCKTILE_INSTALL_EXAMPLES)
    set(SIMPLEDOCK_INTERNAL "INTERNAL")
endif()

add_simple_executable(simpledock
    ${SIMPLEDOCK_INTERNAL}
    LIBRARIES qtdocktile
    INCLUDES ../../src/lib
    QT Core Gui Widgets
)

if(QT_QTDOCKTILE_INSTALL_EXAMPLES AND UNIX AND NOT APPLE)
    install(FILES simpledock.desktop DESTINATION /usr/share/applications)
endif()
