#include "windowstaskbar.h"
#include <QSysInfo>
#include <QtPlugin>
#include "wrapper/taskbar.h"
#include <QApplication>

WindowsTaskBar::WindowsTaskBar(QObject *parent) :
	QtDockProvider(parent)
{
}

WindowsTaskBar::~WindowsTaskBar()
{
}

bool WindowsTaskBar::isUsable() const
{
	return QSysInfo::windowsVersion() >= QSysInfo::WV_WINDOWS7;
}

void WindowsTaskBar::setMenu(QMenu *menu)
{
}

void WindowsTaskBar::setIcon(const QIcon &icon)
{
}

void WindowsTaskBar::setBadge(const QString &badge)
{
}

void WindowsTaskBar::setProgress(int percents)
{
	setProgressValue(qApp->activeWindow()->winId(), percents);
}

void WindowsTaskBar::alert(bool on)
{
	if (on)
		qApp->alert(qApp->activeWindow(), 5000);
	else
		qApp->alert(qApp->activeWindow());
}

Q_EXPORT_PLUGIN2(WindowsTaskBar, WindowsTaskBar)
