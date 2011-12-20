#ifndef MACDOCKTILE_H
#define MACDOCKTILE_H

#include <qtdockprovider.h>

class QtMacDockTilePrivate;
class QtMacDockTile : public QtDockProvider
{
    Q_OBJECT
public:
    QtMacDockTile(QObject *parent = 0);
    virtual ~QtMacDockTile();
    virtual bool isUsable() const;
    virtual void setMenu(QMenu *menu);
    virtual void setIcon(const QIcon &icon);
    virtual void setBadge(const QString &badge);
    virtual void setProgress(int percents);
    virtual void alert(bool on);
private:
    void updateDockIcon();
};

#endif // MACDOCKTILE_H
