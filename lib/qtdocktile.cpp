/****************************************************************************
 *  qtdocktile.cpp
 *
 *  Copyright (c) 2011 by Sidorov Aleksey <gorthauer87@ya.ru>
 *
 ***************************************************************************
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.

 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA
 *
*****************************************************************************/

#include "qtdocktile_p.h"
#include "qtdockmanager_p.h"
#include "qtdockprovider.h"
#include <QMenu>

static QtDockManager *manager()
{
    return QtDockManager::instance();
}

QtDockTile::QtDockTile(QObject *parent) :
    QObject(parent)
{
    connect(manager(), SIGNAL(badgeChanged(QString)), SIGNAL(badgeChanged(QString)));
    connect(manager(), SIGNAL(menuChanged(QMenu*)), SIGNAL(menuChanged(QMenu*)));
    connect(manager(), SIGNAL(progressChanged(int)), SIGNAL(progressChanged(int)));
}

QtDockTile::~QtDockTile()
{
}

void QtDockTile::setMenu(QMenu *menu)
{
    manager()->setMenu(menu);
}

QMenu *QtDockTile::menu() const
{
    return manager()->menu();
}

void QtDockTile::setBadge(const QString &text)
{
    manager()->setBadge(text);
}

QString QtDockTile::badge() const
{
    return manager()->badge();
}

void QtDockTile::setProgress(int percent)
{
    manager()->setProgress(percent);
}

int QtDockTile::progress() const
{
    return manager()->progress();
}

void QtDockTile::alert(bool on)
{
	manager()->alert(on);
}

void QtDockTile::setBadge(int count)
{
	manager()->setBadge(QString::number(count));
}
