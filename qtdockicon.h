#ifndef QTDOCKICON_H
#define QTDOCKICON_H

#include "QtDockIcon_global.h"
#include <QObject>

class QMenu;
class QIcon;
class QtDockIconPrivate;
class QTDOCKICONSHARED_EXPORT QtDockIcon : public QObject
{
	Q_DECLARE_PRIVATE(QtDockIcon)
	Q_OBJECT
public:
	QtDockIcon(QObject *parent = 0);
	virtual ~QtDockIcon();
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
	QScopedPointer<QtDockIconPrivate> d_ptr;
};

#endif // QTDOCKICON_H
