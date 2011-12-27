#include "jumplistsmenuexporter_p.h"
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
	Q_D(JumpListsMenuExporter);
	d->actionInfoList.clear();
	d->updateJumpLists();
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
		//Don't serialize unsupported type of actions. Only invokable actions is supported by platform
		if (!action->menu()
			 &&  action->isVisible()
			 &&  action->isEnabled()
			 && !action->isCheckable())
			list.append(serialize(action));

		if (action->menu())
			foreach (ActionInfo info, serialize(action->menu()))
				list.append(info);
	}
	return list;
}

ActionInfo JumpListsMenuExporterPrivate::serialize(QAction *action)
{
	Data *data = new Data(action);
	ActionType type = action->isSeparator() ? ActionTypeSeparator
														 : ActionTypeNormal;
	ActionInfo info;
	info.id = data->id.constData();
	info.name = data->name.data();
	info.description = data->description.data();
	info.iconPath = data->iconPath.data();
	info.icon = action->icon().pixmap(pixmapSize()).toWinHICON();
	info.type = type;
	info.data = data;
	return info;
}

QSize JumpListsMenuExporterPrivate::pixmapSize() const
{
	int size = qApp->style()->pixelMetric(QStyle::PM_ListViewIconSize);
	return QSize(size, size);
}

void JumpListsMenuExporterPrivate::setAppId(const QString &id)
{
	appId = toWCharArray(id);
	setApplicationId(appId.data());
}

void JumpListsMenuExporterPrivate::updateJumpLists()
{
	ActionInfoList list;
	if(!menu.isNull()) {
		list = serialize(menu.data());
		setJumpLists(list.data(), list.size());
	}
	foreach (ActionInfo info, actionInfoList)
		delete info.data;
	actionInfoList = list;
}
