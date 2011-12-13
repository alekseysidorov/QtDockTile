#include "unitylauncher.h"
#include <QApplication>
#include <dbusmenuexporter.h>
#include <QDBusMessage>
#include <QtPlugin>

#include <QDebug>

template <typename T>
void UnityLauncher::sendMessage(const char *name, const T &value)
{
	QString path = '/' + qAppName();
	QString appPath = QString("application://%1.desktop").arg(qAppName());

	QDBusMessage message = QDBusMessage::createSignal(path, "com.canonical.Unity.LauncherEntry", "Update");
	QVariantList args;
	QVariantMap map;
	map.insert(QLatin1String(name), value);
	args << appPath
		 << map;
	message.setArguments(args);
	QDBusConnection::sessionBus().send(message);
}

UnityLauncher::UnityLauncher(QObject *parent) :
	QtDockProvider(parent)
{
}

UnityLauncher::~UnityLauncher()
{
}

bool UnityLauncher::isUsable() const
{
	return true; //TODO check com.canonical.Unity interface
}

void UnityLauncher::setMenu(QMenu *menu)
{
	if (menu)
		m_menuExporter.reset(new DBusMenuExporter("/" + qAppName(), menu));
	sendMessage("quicklist", menu ? "/" + qAppName() : QString());
}

void UnityLauncher::setIcon(const QIcon &icon)
{
	qApp->setWindowIcon(icon);
}

void UnityLauncher::setBadge(const QString &badge)
{
	bool ok;
	quint64 count = badge.toUInt(&ok);
	if (!ok)
		qWarning("Unity launcher doesn't support string badges");

	sendMessage("count", count);
	sendMessage("count-visible", count > 0);
}

void UnityLauncher::setProgress(int percents)
{
	int progress = qBound(0, percents, 100);
	sendMessage("progress", static_cast<double>(progress)/100.0);
	sendMessage("progress-visible", progress > 0);
}

void UnityLauncher::alert(bool on)
{
	sendMessage("urgent", on);
}

Q_EXPORT_PLUGIN2(UnityLauncher, UnityLauncher)
