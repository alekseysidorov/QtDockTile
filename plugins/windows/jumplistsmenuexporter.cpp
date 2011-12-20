#include "jumplistsmenuexporter_p.h"

struct Data
{
	QWeakPointer<QAction> action;
};

void invokeQAction(void *pointer)
{
	Data *data = reinterpret_cast<Data*>(pointer);
	if (data->action)
		data->action.data()->trigger();
}

JumpListsMenuExporter::JumpListsMenuExporter(QMenu *menu) :
	QObject(menu),
	d_ptr(new JumpListsMenuExporterPrivate(this))
{
	setMenu(menu);
}

JumpListsMenuExporter::~JumpListsMenuExporter()
{
}

void JumpListsMenuExporter::setMenu(QMenu *menu)
{
	Q_D(JumpListsMenuExporter);
	if (d->menu.data())
		d->menu.data()->removeEventFilter(this);
	d->menu = menu;
	if (menu)
		menu->installEventFilter(this);
	d->updateJumpLists();
}

QMenu *JumpListsMenuExporter::menu() const
{
	return d_func()->menu.data();
}

bool JumpListsMenuExporter::eventFilter(QObject *obj, QEvent *ev)
{
	return QObject::eventFilter(obj, ev);
}

ActionInfoList JumpListsMenuExporterPrivate::serialize(QMenu *menu)
{
	ActionInfoList list;
	foreach (QAction *action, menu->actions()) {
		list.append(serialize(action));
		if (action->menu())
			foreach (ActionInfoV2 info, serialize(action->menu()))
				list.append(info);
	}
	return list;
}

ActionInfoV2 JumpListsMenuExporterPrivate::serialize(QAction *action)
{
	ActionInfoV2 info;
	return info;
}

void JumpListsMenuExporterPrivate::updateJumpLists()
{
	actionInfoList.clear();
	if(menu.isNull())
		return;

	actionInfoList = serialize(menu.data());
	setJumpLists(actionInfoList.data(), actionInfoList.size());
}
