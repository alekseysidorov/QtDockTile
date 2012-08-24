find_package(PkgConfig)
pkg_check_modules(DBUSMENUQT dbusmenu-qt>=0.8.1)

find_package(Qt4 COMPONENTS QtDBus QUIET)
if(NOT QT_QTDBUS_FOUND OR NOT DBUSMENUQT_FOUND)
    message(STATUS "Cannot build unity plugin")
    return()
endif(NOT QT_QTDBUS_FOUND OR NOT DBUSMENUQT_FOUND) 

add_docktile_plugin(unityplugin)
target_link_libraries(unityplugin
    ${DBUSMENUQT_LIBRARIES}
    ${QT_QTDBUS_LIBRARY}
)
include_directories(
    ${DBUSMENUQT_INCLUDE_DIRS}
    ${QT_QTDBUS_INCLUDE_DIR}
)
