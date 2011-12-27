#ifndef JUMPLISTSMENUEXPORTER_P_H
#define JUMPLISTSMENUEXPORTER_P_H
#include "jumplistsmenuexporter.h"
#include <QWeakPointer>
#include <QMenu>
#include <QApplication>
#include "wrapper/taskbar.h"
#include "temporaryicon.h"
#include <QDebug>
#include <QUuid>

struct Data;
typedef QVector<ActionInfo> ActionInfoList;
typedef QVector<wchar_t> WCharArray;

static WCharArray toWCharArray(const QString &str)
{
	WCharArray array(str.length() + 1);
	str.toWCharArray(array.data());
	return array;
}

struct Data
{
	Data(QAction *action) : action(action), icon(action->icon()),
		id(QUuid::createUuid().toByteArray()),
		name(toWCharArray(action->text())),
		description(toWCharArray(action->toolTip())),
		iconPath(toWCharArray(icon.filePath()))
	{
	}
	QWeakPointer<QAction> action;
	TemporaryIcon icon;
	QByteArray id;
	WCharArray name;
	WCharArray description;
	WCharArray iconPath;
};

void invokeQAction(void *pointer)
{
	Data *data = reinterpret_cast<Data*>(pointer);
	if (data->action) {
		qDebug() << data->action.data();
		data->action.data()->trigger();
	}
}

class JumpListsMenuExporter;
class JumpListsMenuExporterPrivate
{
	Q_DECLARE_PUBLIC(JumpListsMenuExporter)
public:
	JumpListsMenuExporterPrivate(JumpListsMenuExporter *q) : q_ptr(q)
	{
		setAppId(qAppName());
		setActionInvoker(invokeQAction);
	}
	~JumpListsMenuExporterPrivate()
	{
	}
	ActionInfoList serialize(QMenu *menu);
	ActionInfo serialize(QAction *action);
	QSize pixmapSize() const;
	void setAppId(const QString &id);

	JumpListsMenuExporter *q_ptr;
	void updateJumpLists();
	QWeakPointer<QMenu> menu;
	ActionInfoList actionInfoList;
	WCharArray appId;
};


#endif // JUMPLISTSMENUEXPORTER_P_H
