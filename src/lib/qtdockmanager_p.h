/****************************************************************************
**
** QtDockTile - crossplatform for the work this docks 
**
** Copyright © 1301 USA
** Copyright © 2012 Sidorov Aleksey <gorthauer87@ya.ru>
**
*****************************************************************************
**
** $QTDOCKTILE_BEGIN_LICENSE$
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU Lesser General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
** See the GNU Lesser General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see http://www.gnu.org/licenses/.
** $QTDOCKTILE_END_LICENSE$
**
****************************************************************************/

/*
  * This file is a part of private API
  */

#ifndef QTDOCKMANAGER_P_H
#define QTDOCKMANAGER_P_H
#include <QObject>
#include <QMenu>
#include "pluginloader_p.h"

class QtDockProvider;
typedef QList<QtDockProvider*> QtDockProviderList;
class QtDockManager : public QObject
{
	Q_OBJECT
public:
	static QtDockManager *instance();
	QtDockProvider* currentProvider() const;
	QtDockProviderList usableProviders() const;

	void setMenu(QMenu *menu);
	QMenu *menu() const;
	//FIXME may be unusable on some platforms
	void setBadge(const QString &text);
	QString badge() const;
	void setProgress(int percent);
	int progress() const;
	void alert(bool on = true);
	QVariant platformInvoke(const QByteArray &method, const QVariant &arguments);
signals:
	void iconChanged(const QIcon &icon);
	void menuChanged(QMenu *menu);
	void badgeChanged(const QString &badje);
	void progressChanged(const int percent);
protected:
	QtDockManager();
	~QtDockManager();
	void addProvider(QtDockProvider *provider);
	void removeProvider(QtDockProvider *provider);
private:
	QScopedPointer<PluginLoader> m_pluginLoader;
	QtDockProviderList m_providers;
	QIcon m_dockIcon;
	QIcon m_overlayIcon;
	QString m_badge;
	QWeakPointer<QMenu> m_menu;
	int m_percent;
};

#endif // QTDOCKMANAGER_P_H

