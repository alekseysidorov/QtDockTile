#ifndef QTDOCKICON_H
#define QTDOCKICON_H

#include "qtdocktile_global.h"
#include <QObject>
#include <QIcon>

class QMenu;
class QtDockTilePrivate;
class QTDOCKTILE_EXPORT QtDockTile : public QObject
{
    Q_DECLARE_PRIVATE(QtDockTile)
	Q_OBJECT

	Q_PROPERTY(QIcon icon READ icon WRITE setIcon NOTIFY iconChanged)
	Q_PROPERTY(QMenu* menu  READ menu WRITE setMenu NOTIFY menuChanged)
	Q_PROPERTY(QString badge READ badge WRITE setBadge NOTIFY badgeChanged)
	Q_PROPERTY(int progress  READ progress WRITE setProgress NOTIFY progressChanged)
public:
    QtDockTile(QObject *parent = 0);
    virtual ~QtDockTile();

    QIcon icon() const;
    QMenu *menu() const;
    QString badge() const;	
    int progress() const;
signals:
    void iconChanged(const QIcon &icon);
    void menuChanged(QMenu *menu);
    void badgeChanged(const QString &badje);
    void progressChanged(const int percent);
public slots:
    void alert(bool on = true);
    void setBadge(const QString &text);
    void setProgress(int percent);
    void setIcon(const QIcon &icon);
	void setMenu(QMenu *menu);
protected:
    QScopedPointer<QtDockTilePrivate> d_ptr;
};

#endif // QTDOCKICON_H
