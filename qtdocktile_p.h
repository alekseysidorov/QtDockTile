#ifndef QTDOCKICON_P_H
#define QTDOCKICON_P_H
#include "qtdocktile.h"
#include <QIcon>

class QtDockTile;
class QtDockTilePrivate
{
	Q_DECLARE_PUBLIC(QtDockTile)
public:
	QtDockTilePrivate(QtDockTile *q) : q_ptr(q) {}
	QtDockTile *q_ptr;
};

#endif // QTDOCKICON_P_H
