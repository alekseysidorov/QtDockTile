#ifndef QTDOCKPROVIDER_H
#define QTDOCKPROVIDER_H

#include <QObject>
#include "qtdocktile_global.h"

class QIcon;
class QMenu;

class QTDOCKTILE_EXPORT QtDockProviderInterface
{
public:
	virtual ~QtDockProviderInterface() {}
	virtual bool isUsable() const = 0;
	virtual void setMenu(QMenu *menu) = 0;
	virtual void setBadge(const QString &badge) = 0;
	virtual void setProgress(int percents) = 0;
	virtual void alert(bool on) = 0;

};
Q_DECLARE_INTERFACE(QtDockProviderInterface, "org.DockProvider")

class QTDOCKTILE_EXPORT QtDockProvider : public QObject, public QtDockProviderInterface
{
	Q_OBJECT
	Q_INTERFACES(QtDockProviderInterface)
public:
	explicit QtDockProvider(QObject *parent = 0);

	QMenu *menu() const;
	QString badge() const;
	int progress() const;
	QWidget *window() const;
signals:
	void isUsableChanged(bool set);
};



#endif // QTDOCKPROVIDER_H
