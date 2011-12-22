#Search for source and headers in source directory
file(GLOB SRC "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file(GLOB HDR "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
moc_wrap_cpp(MOC_SRC ${HDR})

# This project will generate library
add_library(qtdocktile STATIC ${SRC} ${HDR} ${MOC_SRC})
#add_definitions(-DQTDOCKTILE_SHARED)
add_definitions(-DQTDOCKTILE_STATIC)

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
