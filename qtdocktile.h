#ifndef QTDOCKICON_H
#define QTDOCKICON_H

#include "qtdocktile_global.h"
#include <QObject>

class QMenu;
class QIcon;
class QtDockTilePrivate;
class QTDOCKTILE_EXPORT QtDockTile : public QObject
{
	Q_DECLARE_PRIVATE(QtDockTile)
	Q_OBJECT
public:
	QtDockTile(QObject *parent = 0);
	virtual ~QtDockTile();
	void setIcon(const QIcon &icon);
	QIcon icon() const;
	void setOverlayIcon(const QIcon &icon);
	QIcon overlayIcon() const;
	void setMenu(QMenu *menu);
	QMenu *menu() const;
	//FIXME may be unusable on some platforms
	void setBadge(const QString &text);
	QString badge() const;
	void setProgress(int percent);
	int progress() const;
public slots:
	void alert(bool on = true);
protected:
	QScopedPointer<QtDockTilePrivate> d_ptr;
};

#endif // QTDOCKICON_H
