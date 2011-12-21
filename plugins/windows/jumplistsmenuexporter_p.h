#ifndef JUMPLISTSMENUEXPORTER_P_H
#define JUMPLISTSMENUEXPORTER_P_H
#include "jumplistsmenuexporter.h"
#include <QWeakPointer>
#include <QMenu>
#include "wrapper/taskbar.h"

struct ActionInfoV2 : public ActionInfo
{
	~ActionInfoV2()
	{
		delete data;
		data = 0;
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
	if (data->action)
		data->action.data()->trigger();
}

class JumpListsMenuExporter;
class JumpListsMenuExporterPrivate
{
	Q_DECLARE_PUBLIC(JumpListsMenuExporter)
public:
	JumpListsMenuExporterPrivate(JumpListsMenuExporter *q) : q_ptr(q) {}
	ActionInfoList serialize(QMenu *menu);
	ActionInfo serialize(QAction *action);
	WCharArray toWCharArray(const QString &str);
	QSize pixmapSize() const;

	JumpListsMenuExporter *q_ptr;
	void updateJumpLists();
	QWeakPointer<QMenu> menu;
	ActionInfoList actionInfoList;
};


#endif // JUMPLISTSMENUEXPORTER_P_H
