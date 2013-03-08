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

#ifndef QTDOCKICON_H
#define QTDOCKICON_H

#include "qtdocktile_global.h"
#include <QObject>
#include <QVariant>
#include <QIcon>

class QMenu;
class QtDockTilePrivate;
class QTDOCKTILE_EXPORT QtDockTile : public QObject
{
	Q_DECLARE_PRIVATE(QtDockTile)
	Q_OBJECT

	Q_PROPERTY(QMenu* menu  READ menu WRITE setMenu NOTIFY menuChanged)
	Q_PROPERTY(QString badge READ badge WRITE setBadge NOTIFY badgeChanged)
	Q_PROPERTY(int progress  READ progress WRITE setProgress NOTIFY progressChanged)
public:
	QtDockTile(QObject *parent = 0);
	QtDockTile(QWidget *widget, QObject *parent = 0);
	virtual ~QtDockTile();

	QMenu *menu() const;
	QString badge() const;
	int progress() const;
	Q_INVOKABLE QVariant platformInvoke(const QByteArray &method, const QVariant &arguments);

	void setBadge(int count);
	void setBadge(const QString &text);
	void setProgress(int percent);
	void setMenu(QMenu *menu);
signals:
	void menuChanged(QMenu *menu);
	void badgeChanged(const QString &badje);
	void progressChanged(int percent);
public slots:
	void alert(bool on = true);
protected:
	QScopedPointer<QtDockTilePrivate> d_ptr;
private:
    void clearBadge();
};

#endif // QTDOCKICON_H

