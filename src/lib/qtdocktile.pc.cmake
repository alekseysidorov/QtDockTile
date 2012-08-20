prefix=${CMAKE_INSTALL_PREFIX}
exec_prefix=${CMAKE_INSTALL_PREFIX}/bin
libdir=${LIB_DESTINATION}
includedir=${QTDOCKTILE_PKG_INCDIR}

Name: qtdocktile
Description: Simple and crossplatform Qt Dock integration
Requires: QtCore QtGui
Version: ${LIBRARY_VERSION}
Libs: ${QTDOCKTILE_PKG_LIBS}
Cflags: -I${QTDOCKTILE_PKG_INCDIR}
