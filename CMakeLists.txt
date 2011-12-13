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

#Search for source and headers in source directory
file(GLOB SRC "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file(GLOB HDR "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
moc_wrap_cpp(MOC_SRCS ${HDR})

# This project will generate library
add_library(qtdocktile SHARED ${SRC} ${HDR} ${MOC_SRCS})
add_definitions(-DQTDOCKTILE_LIBRARY)

include_directories(${CMAKE_CURRENT_BINARY_DIR}
        .
)
update_compiler_flags(qtdocktile)

target_link_libraries(qtdocktile
        ${QT_LIBRARIES}
)

install(TARGETS qtdocktile
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)

add_subdirectory(plugins)
add_subdirectory(example)
