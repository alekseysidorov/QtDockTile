project(quickdocktile)

find_package(Qt4 COMPONENTS QtDeclarative)
if(NOT QT_QTDECLARATIVE_FOUND)
        message(STATUS "Cannot build quick binding")
        return()
endif(NOT QT_QTDECLARATIVE_FOUND)

set(QMLDIR "${CMAKE_CURRENT_SOURCE_DIR}/qmldir")
# Search for source and headers in source directory
file(GLOB SRC "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file(GLOB HDR "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
file(GLOB RESOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.qrc")

qt4_add_resources(RCC ${RESOURCES})
moc_wrap_cpp(MOC_SRCS ${HDR})

# This project will generate library
add_library(quickdocktile SHARED ${SRC} ${HDR} ${RCC} ${MOC_SRCS})

include_directories(${CMAKE_CURRENT_BINARY_DIR}
    .
    ../../lib
    ${QT_QTDECLARATIVE_INCLUDE_DIR}
)

target_link_libraries(quickdocktile
    qtdocktile
    ${QT_LIBRARIES}
	${QT_QTDECLARATIVE_LIBRARY}
    )

set(IMPORTSDIR ${QT_IMPORTS_DIR})
set(IMPORT_DESTINATION ${IMPORTSDIR}/Playground)
install(TARGETS quickdocktile
    RUNTIME DESTINATION ${IMPORT_DESTINATION}
    LIBRARY DESTINATION ${IMPORT_DESTINATION}
)
install(FILES ${QMLDIR}
    DESTINATION ${IMPORT_DESTINATION}
)
