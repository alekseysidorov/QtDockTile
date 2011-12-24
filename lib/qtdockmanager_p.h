#ifndef QTDOCKMANAGER_P_H
#define QTDOCKMANAGER_P_H
#include <QObject>
#include <QMenu>

class QtDockProvider;
typedef QList<QtDockProvider*> QtDockProviderList;
class QtDockManager : public QObject
{
    Q_OBJECT
public:
    static QtDockManager *instance();
    QtDockProviderList usableProviders() const;

    void setMenu(QMenu *menu);
    QMenu *menu() const;
    //FIXME may be unusable on some platforms
    void setBadge(const QString &text);
    QString badge() const;
    void setProgress(int percent);
    int progress() const;
    void alert(bool on = true);
signals:
    void iconChanged(const QIcon &icon);
    void menuChanged(QMenu *menu);
    void badgeChanged(const QString &badje);
    void progressChanged(const int percent);
protected:
    QtDockManager();
	void addProvider(QtDockProvider *provider);
	void removeProvider(QtDockProvider *provider);
private:
    QtDockProviderList m_providers;
    QIcon m_dockIcon;
    QIcon m_overlayIcon;
    QString m_badge;
    QWeakPointer<QMenu> m_menu;
    int m_percent;
};

#endif // QTDOCKMANAGER_P_H
