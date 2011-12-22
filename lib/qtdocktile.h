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

	Q_PROPERTY(QMenu* menu  READ menu WRITE setMenu NOTIFY menuChanged)
	Q_PROPERTY(QString badge READ badge WRITE setBadge NOTIFY badgeChanged)
	Q_PROPERTY(int progress  READ progress WRITE setProgress NOTIFY progressChanged)
public:
    QtDockTile(QObject *parent = 0);
    virtual ~QtDockTile();

    QMenu *menu() const;
    QString badge() const;	
    int progress() const;
signals:
    void menuChanged(QMenu *menu);
    void badgeChanged(const QString &badje);
    void progressChanged(const int percent);
public slots:
    void alert(bool on = true);
	void setBadge(int count);
    void setBadge(const QString &text);
    void setProgress(int percent);
	void setMenu(QMenu *menu);
protected:
    QScopedPointer<QtDockTilePrivate> d_ptr;
};

#endif // QTDOCKICON_H
