#include "qtdockmanager_p.h"
#include "qtdockprovider.h"

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

void QtDockManager::setIcon(const QIcon &icon)
{
	m_dockIcon = icon;
	_providers->setIcon(icon);
	emit iconChanged(icon);
}

QIcon QtDockManager::icon() const
{
	return m_dockIcon;
}

void QtDockManager::setOverlayIcon(const QIcon &icon)
{
	m_overlayIcon = icon;
	_providers->setOverlayIcon(icon);
	emit overlayIconChanged(icon);
}

QIcon QtDockManager::overlayIcon() const
{
	return m_overlayIcon;
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

}

void QtDockManager::addProvider(QtDockProvider *provider)
{
	m_providers.append(provider);
}

void QtDockManager::removeProvider(QtDockProvider *provider)
{
	m_providers.removeAll(provider);
}
