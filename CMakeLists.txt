cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

if(COMMAND cmake_policy)
    cmake_policy (SET CMP0003 NEW)
endif(COMMAND cmake_policy)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(QT_USE_QTGUI true)
set(QT_USE_QTCORE true)
set(CMAKE_AUTOMOC true)
set(QT_MIN_VERSION "4.7.0")

find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})
include(CommonUtils)

define_bundle_paths(qtdocktile)
add_simple_library(qtdocktile SHARED)

add_subdirectory(plugins)