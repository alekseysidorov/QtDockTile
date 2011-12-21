#include "jumplistsmenuexporter_p.h"
#include <QUuid>
#include <QApplication>
#include <QStyle>

JumpListsMenuExporter::JumpListsMenuExporter(QObject *parent) :
	QObject(parent),
	d_ptr(new JumpListsMenuExporterPrivate(this))
{
}


JumpListsMenuExporter::JumpListsMenuExporter(QMenu *menu, QObject *parent) :
	QObject(parent),
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
			foreach (ActionInfo info, serialize(action->menu()))
				list.append(info);
	}
	return list;
}

ActionInfo JumpListsMenuExporterPrivate::serialize(QAction *action)
{
	QString id = QUuid::createUuid().toString();

	Data *data = new Data;

	data->action = action;
	data->id = toWCharArray(id);
	data->name = toWCharArray(action->text());
	data->description = toWCharArray(action->toolTip());

	ActionType type = (action->isSeparator() || action->menu()) ? ActionTypeSeparator
																: ActionTypeNormal;
	ActionInfo info;
	info.id = data->id.data();
	info.name = data->name.data();
	info.description = data->description.data();
	info.icon = action->icon().pixmap(pixmapSize()).toWinHICON();
	info.type = type;
	info.data = data;
	return info;
}

WCharArray JumpListsMenuExporterPrivate::toWCharArray(const QString &str)
{
	WCharArray array(str.length() + 1);
	str.toWCharArray(array.data());
	return array;
}

QSize JumpListsMenuExporterPrivate::pixmapSize() const
{
	int size = qApp->style()->pixelMetric(QStyle::PM_ListViewIconSize);
	return QSize(size, size);
}

void JumpListsMenuExporterPrivate::updateJumpLists()
{
	foreach (ActionInfo info, actionInfoList)
		delete info.data;
	actionInfoList.clear();
	if(menu.isNull())
		return;

	actionInfoList = serialize(menu.data());
	setJumpLists(actionInfoList.data(), actionInfoList.size());
}
