#include "quickdocktile.h"

#include <QtDeclarative>
#include <qtdocktile.h>
#include <QDebug>

QuickDockTile::QuickDockTile()
{
	qDebug() << Q_FUNC_INFO;
}

void QuickDockTile::registerTypes(const char *uri)
{
	Q_ASSERT(uri == QLatin1String("org.quickdocktile"));

	qmlRegisterType<QtDockTile>(uri, 1, 0, "DockTile");
}

Q_EXPORT_PLUGIN2(quickdocktile, QuickDockTile)
