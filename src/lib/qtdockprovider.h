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

#ifndef QTDOCKPROVIDER_H
#define QTDOCKPROVIDER_H

#include <QObject>
#include "qtdocktile_global.h"
#include <QVariant>

class QIcon;
class QMenu;

class QTDOCKTILE_EXPORT QtDockProviderInterface
{
public:
	virtual ~QtDockProviderInterface() {}
	virtual bool isUsable() const = 0;
	virtual void setMenu(QMenu *menu) = 0;
	virtual void setBadge(const QString &badge) = 0;
	virtual void clearBadge() = 0;
	virtual void setProgress(int percents) = 0;
	virtual void alert(bool on) = 0;
	virtual QVariant platformInvoke(const QByteArray &method, const QVariant &arguments);
};

#define docktileProvider_iid \
	"org.DockTile.Provider"

Q_DECLARE_INTERFACE(QtDockProviderInterface, docktileProvider_iid)

class QTDOCKTILE_EXPORT QtDockProvider : public QObject, public QtDockProviderInterface
{
	Q_OBJECT
	Q_INTERFACES(QtDockProviderInterface)
public:
	explicit QtDockProvider(QObject *parent = 0);

	QMenu *menu() const;
	QString badge() const;
	int progress() const;
	QWidget *window() const;
signals:
	void isUsableChanged(bool set);
};



#endif // QTDOCKPROVIDER_H

