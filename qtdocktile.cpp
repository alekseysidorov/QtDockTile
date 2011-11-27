#include "qtdocktile_p.h"

QtDockTile::QtDockTile(QObject *parent) :
	QObject(parent)
{
}

QtDockTile::~QtDockTile()
{
}

void QtDockTile::setIcon(const QIcon &icon)
{
}

QIcon QtDockTile::icon() const
{
}

void QtDockTile::setOverlayIcon(const QIcon &icon)
{
}

QIcon QtDockTile::overlayIcon() const
{
}

void QtDockTile::setMenu(QMenu *menu)
{
}

QMenu *QtDockTile::menu() const
{
}

void QtDockTile::setBadge(const QString &text)
{
}

QString QtDockTile::badge() const
{
}

void QtDockTile::setProgress(int percent)
{
}

int QtDockTile::progress() const
{
}

void QtDockTile::alert(bool on)
{
}
