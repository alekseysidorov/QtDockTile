/****************************************************************************
**
** QtDockTile - crossplatform for the work this docks 
**
** Copyright © 2012 Aleksey Sidorov <gorthauer87@ya.ru>
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
#ifndef PLUGINLOADER_H
#define PLUGINLOADER_H
#include <QObject>
#include <QMutex>
#include <QPluginLoader>

class PluginLoader
{
public:
    PluginLoader(const QString &category, const char *interfaceId = 0);
    ~PluginLoader();
    QObjectList instances();
    template <typename T>
    QList<T*> instances();
private:
    void load();
    QStringList pluginList() const;

    QByteArray m_interfaceId;
    QMutex m_mutex;
    QString m_location;
    QList<QPluginLoader*> m_plugins;
};

template <typename T>
Q_INLINE_TEMPLATE QList<T*> PluginLoader::instances()
{
    QMutexLocker locker(&m_mutex);
    Q_UNUSED(locker);

    QList<T*> list;
    for (int i = 0; i < m_plugins.count(); i++) {
        //fast cast and os x workaround
        if (!m_interfaceId.isEmpty())
            list << static_cast<T*>(m_plugins.at(i)->instance());
        T *obj = qobject_cast<T*>(m_plugins.at(i)->instance());
        if (obj)
            list << obj;
    }
    return list;
}

#endif // PLUGINLOADER_H

