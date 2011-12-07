#include "qtdockmanager_p.h"
#include "qtdockprovider.h"

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
