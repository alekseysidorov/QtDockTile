find_library(COCOA_LIBRARIES Cocoa)
add_docktile_plugin(macdocktile)
target_link_libraries(macdocktile ${COCOA_LIBRARIES})
