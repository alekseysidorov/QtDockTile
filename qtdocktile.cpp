#include "qtdocktile_p.h"
#include "qtdockmanager_p.h"
#include "qtdockprovider.h"
#include <QMenu>

static QtDockManager *manager()
{
    return QtDockManager::instance();
}

QtDockTile::QtDockTile(QObject *parent) :
    QObject(parent)
{
    connect(manager(), SIGNAL(badgeChanged(QString)), SIGNAL(badgeChanged(QString)));
    connect(manager(), SIGNAL(iconChanged(QIcon)), SIGNAL(iconChanged(QIcon)));
    connect(manager(), SIGNAL(menuChanged(QMenu*)), SIGNAL(menuChanged(QMenu*)));
    connect(manager(), SIGNAL(progressChanged(int)), SIGNAL(progressChanged(int)));
}

QtDockTile::~QtDockTile()
{
}

void QtDockTile::setIcon(const QIcon &icon)
{
    manager()->setIcon(icon);
}

QIcon QtDockTile::icon() const
{
    return manager()->icon();
}

void QtDockTile::setMenu(QMenu *menu)
{
    manager()->setMenu(menu);
}

QMenu *QtDockTile::menu() const
{
    return manager()->menu();
}

void QtDockTile::setBadge(const QString &text)
{
    manager()->setBadge(text);
}

QString QtDockTile::badge() const
{
    return manager()->badge();
}

void QtDockTile::setProgress(int percent)
{
    manager()->setProgress(percent);
}

int QtDockTile::progress() const
{
    return manager()->progress();
}

void QtDockTile::alert(bool on)
{
    manager()->alert(on);
}
