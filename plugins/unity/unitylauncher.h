#ifndef UNITYLAUNCHER_H
#define UNITYLAUNCHER_H
#include <qtdockprovider.h>
#include <QWeakPointer>

class DBusMenuExporter;
class UnityLauncher : public QtDockProvider
{
	Q_OBJECT
	Q_INTERFACES(QtDockProvider)
public:
	explicit UnityLauncher(QObject *parent = 0);
	virtual ~UnityLauncher();
	virtual bool isUsable() const;
	virtual void setMenu(QMenu *menu);
	virtual void setIcon(const QIcon &icon);
	virtual void setBadge(const QString &badge);
	virtual void setProgress(int percents);
	virtual void alert(bool on);
private:
	template <typename T>
	void sendMessage(const char *, const T &);
	QScopedPointer<DBusMenuExporter> m_menuExporter;
};

#endif // UNITYLAUNCHER_H
