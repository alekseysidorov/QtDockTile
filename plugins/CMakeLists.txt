#fixme, write find modules and platform checks

macro(ADD_DOCKTILE_PLUGIN target)
	message(STATUS "Searching ${target} source and headers")

	# Search for source and headers in source directory
	file(GLOB_RECURSE SRC "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
	file(GLOB_RECURSE HDR "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
	file(GLOB_RECURSE FORMS "${CMAKE_CURRENT_SOURCE_DIR}/*.ui")
	if (apple)
		file(GLOB_RECURSE SOURCES_MM RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/" "${CMAKE_CURRENT_SOURCE_DIR}/*.mm" )
		list(APPEND SOURCE SOURCE_MM} )
	endif()

	qt4_wrap_ui(UIS_H ${FORMS})
	moc_wrap_cpp(MOC_SRCS ${HDR})

	# This project will generate library, TODO use MODULE instead SHARED
	add_library(${target} SHARED ${SRC} ${HDR} ${UIS_H} ${SOURCE_MM} ${MOC_SRCS})

	include_directories(${CMAKE_CURRENT_BINARY_DIR}
		.
	)
	update_compiler_flags(${target})

	target_link_libraries(${target}
		${QT_LIBRARIES}
		qtdocktile
	)

	install(TARGETS ${target}
                RUNTIME DESTINATION "${PLUGINDIR}/docktile"
                LIBRARY DESTINATION "${PLUGINDIR}/docktile"
	)
endmacro()

if(APPLE)
	add_subdirectory(mac)
elseif(UNIX)
	add_subdirectory(unity)
	add_subdirectory(dockmanager)
elseif(WIN32)
	add_subdirectory(windows)	
endif()
