#include "qtdockicon_p.h"

QtDockIcon::QtDockIcon(QObject *parent) :
	QObject(parent)
{
}

QtDockIcon::~QtDockIcon()
{
}

void QtDockIcon::setIcon(const QIcon &icon)
{
}

QIcon QtDockIcon::icon() const
{
}

void QtDockIcon::setOverlayIcon(const QIcon &icon)
{
}

QIcon QtDockIcon::overlayIcon() const
{
}

void QtDockIcon::setMenu(QMenu *menu)
{
}

QMenu *QtDockIcon::menu() const
{
}

void QtDockIcon::setBadge(const QString &text)
{
}

QString QtDockIcon::badge() const
{
}

void QtDockIcon::setProgress(int percent)
{
}

int QtDockIcon::progress() const
{
}

void QtDockIcon::alert(bool on)
{
}
