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
		delete id;
		delete name;
		delete description;
		delete data;
	}
};
typedef QVector<ActionInfoV2> ActionInfoList;

class JumpListsMenuExporter;
class JumpListsMenuExporterPrivate
{
	Q_DECLARE_PUBLIC(JumpListsMenuExporter)
public:
	JumpListsMenuExporterPrivate(JumpListsMenuExporter *q) : q_ptr(q) {}
	JumpListsMenuExporter *q_ptr;
	void updateJumpLists();
	QWeakPointer<QMenu> menu;
	ActionInfoList actionInfoList;
};


#endif // JUMPLISTSMENUEXPORTER_P_H
