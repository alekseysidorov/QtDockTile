add_docktile_plugin(windowstaskbar)
target_link_libraries(windowstaskbar "dwmapi.lib")
add_definitions(-DTASKWRAPPER)
