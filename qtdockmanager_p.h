#ifndef QTDOCKMANAGER_P_H
#define QTDOCKMANAGER_P_H
#include <QList>

class QtDockProvider;
typedef QList<QtDockProvider*> QtDockProviderList;
class QtDockManager
{
	Q_DISABLE_COPY(QtDockManager)
public:
	static QtDockManager *instance();
	QtDockProviderList usableProviders() const;
protected:
	QtDockManager();
	void addProvider(QtDockProvider *provider);
	void removeProvider(QtDockProvider *provider);
private:
	QtDockProviderList m_providers;
};

#endif // QTDOCKMANAGER_P_H
