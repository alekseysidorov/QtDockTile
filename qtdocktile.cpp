#include "qtdocktile_p.h"
#include "qtdockmanager_p.h"
#include "qtdockprovider.h"
#include <QMenu>

static QtDockProviderList usableProviders()
{
	return QtDockManager::instance()->usableProviders();
}
//some sugar
#define _providers \
	foreach (QtDockProvider *provider, usableProviders()) \
		provider \

QtDockTile::QtDockTile(QObject *parent) :
	QObject(parent)
{
}

QtDockTile::~QtDockTile()
{
}

void QtDockTile::setIcon(const QIcon &icon)
{
	Q_D(QtDockTile);
	d->dockIcon = icon;
	_providers->setIcon(icon);
}

QIcon QtDockTile::icon() const
{
	return d_func()->dockIcon;
}

void QtDockTile::setOverlayIcon(const QIcon &icon)
{
	Q_D(QtDockTile);
	d->overlayIcon = icon;
	_providers->setOverlayIcon(icon);
}

QIcon QtDockTile::overlayIcon() const
{
	return d_func()->overlayIcon;
}

void QtDockTile::setMenu(QMenu *menu)
{
	Q_D(QtDockTile);
	d->menu = menu;
	_providers->setMenu(menu);
}

QMenu *QtDockTile::menu() const
{
	return d_func()->menu.data();
}

void QtDockTile::setBadge(const QString &text)
{
	Q_D(QtDockTile);
	d->badge = text;
	_providers->setBadge(text);
}

QString QtDockTile::badge() const
{
	return d_func()->badge;
}

void QtDockTile::setProgress(int percent)
{
	Q_D(QtDockTile);
	d->percent = percent;
	_providers->setProgress(percent);
}

int QtDockTile::progress() const
{
	return d_func()->percent;
}

void QtDockTile::alert(bool on)
{
	_providers->alert(on);
}
