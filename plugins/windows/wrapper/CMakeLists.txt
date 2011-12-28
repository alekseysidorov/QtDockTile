	#Search for source and headers in source directory
file(GLOB SRC "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file(GLOB HDR "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
file(GLOB FORMS "${CMAKE_CURRENT_SOURCE_DIR}/*.ui")
file(GLOB QRC "${CMAKE_CURRENT_SOURCE_DIR}/*.qrc")

qt4_wrap_ui(UIS_H ${FORMS})
moc_wrap_cpp(MOC_SRCS ${HDR})
qt4_add_resources(QRC_SOURCES ${QRC})

# This project will generate library
add_library(wrapper SHARED ${SRC} ${MM} ${HDR} ${UIS_H} ${MOC_SRCS} ${QRC_SOURCES})
add_definitions(-DTASKWRAPPER)

include_directories(${CMAKE_CURRENT_BINARY_DIR}
	.
)

target_link_libraries(wrapper
	"dwmapi" "Shlwapi" "ws2_32"
)
set_target_properties(windowstaskbar PROPERTIES COMPILE_FLAGS "/Zc:wchar_t-") # do not treat wchar_t as built-in type

install(TARGETS wrapper
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
)
