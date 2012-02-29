project(simpledock)

file(GLOB_RECURSE SRC "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE HDR "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
file(GLOB_RECURSE FORMS "${CMAKE_CURRENT_SOURCE_DIR}/*.ui")
file(GLOB_RECURSE QRC "${CMAKE_CURRENT_SOURCE_DIR}/*.qrc")

qt4_wrap_ui(UIS_H ${FORMS})
moc_wrap_cpp(MOC_SRC ${HDR})
qt4_add_resources(QRC_SOURCES ${QRC})

# This project will generate library
add_executable(simpledock MACOSX_BUNDLE WIN32 ${SRC} ${HDR} ${UIS_H} ${QML_DIR} ${MOC_SRC} ${QRC_SOURCES})

include_directories(${CMAKE_CURRENT_BINARY_DIR}
    .
    ../../src/lib
)

target_link_libraries(simpledock qtdocktile ${QT_LIBRARIES} ${QT_QTMAIN_LIBRARY})

if(UNIX AND NOT APPLE)
    install(FILES simpledock.desktop DESTINATION share/applications)
endif()

install(TARGETS simpledock DESTINATION bin)
