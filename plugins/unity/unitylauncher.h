#ifndef UNITYLAUNCHER_H
#define UNITYLAUNCHER_H
#include <qtdockprovider.h>
#include <QWeakPointer>
#include <QVariant>

class DBusMenuExporter;
class UnityLauncher : public QtDockProvider
{
	Q_OBJECT
public:
	explicit UnityLauncher(QObject *parent = 0);
	virtual ~UnityLauncher();
	virtual bool isUsable() const;
	virtual void setMenu(QMenu *menu);
	virtual void setIcon(const QIcon &icon);
	virtual void setBadge(const QString &badge);
	virtual void setProgress(int percents);
	virtual void alert(bool on);
protected:
	QString appDesktopUri() const;
	QString appUri() const;
private:
	template <typename T>
	void sendMessage(const char *method, const T &value);
	void sendMessage(const QVariantMap &properties);
	QScopedPointer<DBusMenuExporter> m_menuExporter;
};

#endif // UNITYLAUNCHER_H
