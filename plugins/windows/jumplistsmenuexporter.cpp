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

void JumpListsMenuExporterPrivate::updateJumpLists()
{
	actionInfoList.clear();

	//...

	setJumpLists(actionInfoList.data(), actionInfoList.size());
}

#include "jumplistsmenuexporter.moc"
