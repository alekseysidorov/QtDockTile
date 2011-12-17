#fixme, write find modules and platform checks

macro(ADD_DOCKTILE_PLUGIN target)
	message(STATUS "Searching ${target} source and headers")

	# Search for source and headers in source directory
	file(GLOB_RECURSE SRC "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
	file(GLOB_RECURSE HDR "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
	file(GLOB_RECURSE FORMS "${CMAKE_CURRENT_SOURCE_DIR}/*.ui")
        if(APPLE)
                file(GLOB_RECURSE MM "${CMAKE_CURRENT_SOURCE_DIR}/*.mm")
	endif()

	qt4_wrap_ui(UIS_H ${FORMS})
	moc_wrap_cpp(MOC_SRC ${HDR})

	# This project will generate library, TODO use MODULE instead SHARED
	add_library(${target} SHARED ${SRC} ${HDR} ${UIS_H} ${MM} ${MOC_SRC})

	include_directories(${CMAKE_CURRENT_BINARY_DIR}
		.
	)

	target_link_libraries(${target}
		qtdocktile
		${QT_LIBRARIES}		
	)

	install(TARGETS ${target}
                RUNTIME DESTINATION "${QT_PLUGINS_DIR}/docktile"
                LIBRARY DESTINATION "${QT_PLUGINS_DIR}/docktile"
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
