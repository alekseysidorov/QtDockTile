#include "windowstaskbar.h"
#include <QSysInfo>
#include <QtPlugin>

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
}

void WindowsTaskBar::alert(bool on)
{
}

Q_EXPORT_PLUGIN2(WindowsTaskBar, WindowsTaskBar)
