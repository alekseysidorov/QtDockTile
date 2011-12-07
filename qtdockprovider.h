#ifndef QTDOCKPROVIDER_H
#define QTDOCKPROVIDER_H

#include <QObject>
#include "qtdocktile_global.h"

class QIcon;
class QMenu;
class QTDOCKTILE_EXPORT QtDockProvider : public QObject
{
	Q_OBJECT
public:
	explicit QtDockProvider(QObject *parent = 0);
	virtual bool isUsable() const = 0;
	virtual void setMenu(QMenu *menu) = 0;
	virtual void setIcon(const QIcon &icon) = 0;
	virtual void setOverlayIcon(const QIcon &icon) = 0;
	virtual void setBadge(const QString &badge) = 0;
	virtual void setProgress(int percents) = 0;
signals:
	void isUsableChanged(bool set);
};

Q_DECLARE_INTERFACE(QtDockProvider, "org.DockProvider")

#endif // QTDOCKPROVIDER_H
