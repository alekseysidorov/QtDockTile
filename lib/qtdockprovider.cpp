#include "qtdockprovider.h"
#include "qtdockmanager_p.h"
#include <QApplication>

QtDockProvider::QtDockProvider(QObject *parent) :
	QObject(parent)
{
}

QMenu *QtDockProvider::menu() const
{
    return QtDockManager::instance()->menu();
}

QIcon QtDockProvider::icon() const
{
    return QtDockManager::instance()->icon();
}

QString QtDockProvider::badge() const
{
    return QtDockManager::instance()->badge();
}

int QtDockProvider::progress() const
{
	return QtDockManager::instance()->progress();
}

QWidget *QtDockProvider::window() const
{
	return qApp->activeWindow();
}
