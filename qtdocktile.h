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

	QIcon icon() const;

	QIcon overlayIcon() const;
	void setMenu(QMenu *menu);
	QMenu *menu() const;
	QString badge() const;

	int progress() const;
signals:
	void iconChanged(const QIcon &icon);
	void overlayIconChanged(const QIcon &icon);
	void menuChanged(QMenu *menu);
	void badgeChanged(const QString &badje);
	void progressChanged(const int percent);
public slots:
	void alert(bool on = true);
	void setBadge(const QString &text);
	void setProgress(int percent);
	void setIcon(const QIcon &icon);
	void setOverlayIcon(const QIcon &icon);
protected:
	QScopedPointer<QtDockTilePrivate> d_ptr;
};

#endif // QTDOCKICON_H
