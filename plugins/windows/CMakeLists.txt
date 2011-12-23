add_docktile_plugin(windowstaskbar)
target_link_libraries(windowstaskbar "dwmapi.lib" "Shlwapi.lib")
add_definitions(-DTASKWRAPPER)

set_target_properties(windowstaskbar PROPERTIES COMPILE_FLAGS "/Zc:wchar_t-") # do not treat wchar_t as built-in type
