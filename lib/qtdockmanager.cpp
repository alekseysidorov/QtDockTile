#include "qtdockmanager_p.h"
#include "qtdockprovider.h"
#include <QPluginLoader>
#include <QLibraryInfo>
#include <QDir>
#include <QLibrary>
#include <QApplication>

//some sugar
#define _providers \
	foreach (QtDockProvider *provider, usableProviders()) \
    provider \

QtDockManager *QtDockManager::instance()
{
    static QtDockManager pointer;
    return &pointer;
}

QtDockProviderList QtDockManager::usableProviders() const
{
    //TODO remove foreach
    QtDockProviderList list;
	foreach (QtDockProvider *provider, m_providers) {
        if (provider->isUsable())
            list.append(provider);
    }
    return list;
}

void QtDockManager::setMenu(QMenu *menu)
{
    m_menu = menu;
    _providers->setMenu(menu);
    emit menuChanged(menu);
}

QMenu *QtDockManager::menu() const
{
    return m_menu.data();
}

void QtDockManager::setBadge(const QString &text)
{
    m_badge = text;
    _providers->setBadge(text);
    emit badgeChanged(text);
}

QString QtDockManager::badge() const
{
    return m_badge;
}

void QtDockManager::setProgress(int percent)
{
    m_percent = percent;
    _providers->setProgress(percent);
    emit progressChanged(percent);
}

int QtDockManager::progress() const
{
    return m_percent;
}

void QtDockManager::alert(bool on)
{
	_providers->alert(on);
}

QtDockManager::QtDockManager()
{
    //resolve plugins
    QStringList plugins;
    QDir dir = QLibraryInfo::location(QLibraryInfo::PluginsPath) + QLatin1String("/docktile");
    foreach (QString filename, dir.entryList())
        if (QLibrary::isLibrary(filename))
            plugins.append(dir.absolutePath() + '/' + filename);

    QPluginLoader loader;
    foreach (QString plugin, plugins) {
        loader.setFileName(plugin);
        if (loader.load()) {
            QtDockProviderInterface *provider = qobject_cast<QtDockProviderInterface*>(loader.instance());
            if (provider)
                addProvider(static_cast<QtDockProvider*>(provider));
            else
                qWarning("Unknow interface in plugin %s", qPrintable(plugin));
        } else
			qWarning("Unable to load plugin %s : %s", qPrintable(plugin), qPrintable(loader.errorString()));
    }
}

void QtDockManager::addProvider(QtDockProvider *provider)
{
    m_providers.append(provider);
}

void QtDockManager::removeProvider(QtDockProvider *provider)
{
    m_providers.removeAll(provider);
}
