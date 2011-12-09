#ifndef MACDOCKTILE_H
#define MACDOCKTILE_H

#include <QtPlugin>
#include <qtdockprovider.h>

class QtMacDockTilePrivate;
class QtMacDockTile : public QtDockProvider
{
	Q_OBJECT
	Q_INTERFACES(QtDockProvider)
	Q_DECLARE_PRIVATE(QtMacDockTile)
public:
	QtMacDockTile(QObject *parent = 0);
	virtual ~QtMacDockTile();
	virtual bool isUsable() const;
	virtual void setMenu(QMenu *menu);
	virtual void setIcon(const QIcon &icon);
	virtual void setOverlayIcon(const QIcon &icon);
	virtual void setBadge(const QString &badge);
	virtual void setProgress(int percents);
	virtual void alert(bool on);
private:
	QScopedPointer<QtMacDockTilePrivate> d_ptr;
};

#endif // MACDOCKTILE_H
