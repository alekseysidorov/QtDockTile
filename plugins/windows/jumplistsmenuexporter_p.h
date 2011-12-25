#ifndef JUMPLISTSMENUEXPORTER_P_H
#define JUMPLISTSMENUEXPORTER_P_H
#include "jumplistsmenuexporter.h"
#include <QWeakPointer>
#include <QMenu>
#include <QApplication>
#include "wrapper/taskbar.h"
#include <QDebug>

struct Data;
struct ActionInfoV2 : public ActionInfo
{
	~ActionInfoV2()
	{
		qDebug() << Q_FUNC_INFO;
	}
};

typedef QVector<ActionInfo> ActionInfoList;
typedef QVector<wchar_t> WCharArray;

struct Data
{
	QWeakPointer<QAction> action;
	WCharArray id;
	WCharArray name;
	WCharArray description;
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
	WCharArray toWCharArray(const QString &str);
	QSize pixmapSize() const;
	void setAppId(const QString &id);

	JumpListsMenuExporter *q_ptr;
	void updateJumpLists();
	QWeakPointer<QMenu> menu;
	ActionInfoList actionInfoList;
	WCharArray appId;
};


#endif // JUMPLISTSMENUEXPORTER_P_H
