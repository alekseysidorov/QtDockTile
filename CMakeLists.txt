project(QtDockTile)
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

if(COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(QT_USE_QTGUI true)
set(QT_USE_QTCORE true)
set(QT_MIN_VERSION "4.7.0")

find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})
include(CommonUtils)

set(CMAKE_QTDOCKTILE_VERSION_MAJOR 1 CACHE INT "Major QtDockTile version number" FORCE)
set(CMAKE_QTDOCKTILE_VERSION_MINOR 0 CACHE INT "Minor QtDockTile version number" FORCE)
set(CMAKE_QTDOCKTILE_VERSION_PATCH 0 CACHE INT "Release QtDockTile version number" FORCE)
set(CMAKE_QTDOCKTILE_VERSION_STRING "${CMAKE_QTDOCKTILE_VERSION_MAJOR}.${CMAKE_QTDOCKTILE_VERSION_MINOR}.${CMAKE_QTDOCKTILE_VERSION_PATCH}" CACHE STRING "QtDockTile version string" FORCE)

add_subdirectory(src)
add_subdirectory(examples)
add_subdirectory(doc)

# uninstall target
configure_file(
	"${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
	"${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
	IMMEDIATE @ONLY)

add_custom_target(uninstall
	COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)

