prefix=${CMAKE_INSTALL_PREFIX}
exec_prefix=${CMAKE_INSTALL_PREFIX}/bin
libdir=${LIB_DESTINATION}
includedir=${CMAKE_INSTALL_PREFIX}/include

Name: qtdocktile
Description: Simple and crossplatform Qt Dock integration
Requires: QtCore QtGui
Version: ${CMAKE_QTDOCKTILE_VERSION_MAJOR}.${CMAKE_QTDOCKTILE_VERSION_MINOR}.${CMAKE_QTDOCKTILE_VERSION_PATCH}
Libs: -L${LIB_DESTINATION} -lqtdocktile
Cflags: -I${CMAKE_INSTALL_PREFIX}/include/QtDockTile

