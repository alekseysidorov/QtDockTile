#ifndef QTDOCKICON_GLOBAL_H
#define QTDOCKICON_GLOBAL_H

#include <QtCore/qglobal.h>

#ifndef QTDOCKTILE_STATIC
#  if defined(QTDOCKTILE_SHARED)
#    define QTDOCKTILE_EXPORT Q_DECL_EXPORT
#  else
#    define QTDOCKTILE_EXPORT Q_DECL_IMPORT
#  endif
#else
#  define QTDOCKTILE_EXPORT
#endif

#endif // QTDOCKICON_GLOBAL_H
