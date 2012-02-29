#Search for source and headers in source directory
file(GLOB SRC "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file(GLOB HDR "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
moc_wrap_cpp(MOC_SRC ${HDR})

# This project will generate library
add_library(qtdocktile
    SHARED
    ${SRC}
    ${HDR}
    ${MOC_SRC}
)

add_public_header(qtdocktile_global.h)
generate_public_header(qtdocktile.h QtDockTile)
generate_public_header(qtdockprovider.h QtDockProvider)

set_target_properties(qtdocktile PROPERTIES
    VERSION ${CMAKE_QTDOCKTILE_VERSION_STRING}
    SOVERSION ${CMAKE_QTDOCKTILE_VERSION_MAJOR}
    DEFINE_SYMBOL QT_DOCKTILE_LIB

    #FRAMEWORK TRUE
    #FRAMEWORK_VERSION ${CMAKE_QTDOCKTILE_VERSION_MAJOR}
    #MACOSX_FRAMEWORK_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/Info.plist.in"
    #MACOSX_FRAMEWORK_BUNDLE_VERSION "QtDockTile ${CMAKE_QTDOCKTILE_VERSION_STRING}"
    #MACOSX_FRAMEWORK_SHORT_VERSION_STRING ${CMAKE_QTDOCKTILE_VERSION_STRING}
    #MACOSX_FRAMEWORK_IDENTIFIER org.docktile
)

include_directories(${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}/include
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
    FRAMEWORK DESTINATION lib
)

install(FILES ${PUBLIC_HEADERS}
    DESTINATION include/QtDockTile
)

