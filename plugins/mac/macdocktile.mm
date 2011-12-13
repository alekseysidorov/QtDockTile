#include "macdocktile.h"

#import <AppKit/NSDockTile.h>
#import <Cocoa/Cocoa.h>
#include <QApplication>
#include <QIcon>
#include <QPainter>

extern void qt_mac_set_dock_menu(QMenu *);

QtMacDockTile::QtMacDockTile(QObject *parent) :
    QtDockProvider(parent)
{
}

QtMacDockTile::~QtMacDockTile()
{

}

bool QtMacDockTile::isUsable() const
{
    return true;
}

void QtMacDockTile::setMenu(QMenu *menu)
{
    qt_mac_set_dock_menu(menu);
}

void QtMacDockTile::setIcon(const QIcon &)
{
    updateDockIcon();
}

void QtMacDockTile::setBadge(const QString &badge)
{
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    NSString* mac_message = [[NSString alloc] initWithUTF8String: badge.toUtf8().constData()];
    NSDockTile *dockTile = [NSApp dockTile];
    [dockTile setBadgeLabel: mac_message];
    [dockTile display];
    [pool release];
}

void QtMacDockTile::setProgress(int)
{
    updateDockIcon();
}

void QtMacDockTile::alert(bool on)
{
    if (on)
        [NSApp requestUserAttention: NSInformationalRequest];
}

void QtMacDockTile::updateDockIcon()
{
    NSDockTile *dockTile = [NSApp dockTile];
    NSSize size = [dockTile size];
    QIcon dockIcon = icon();
    if (progress() > 0) {
        //TODO write progressBar
        QPixmap pixmap = dockIcon.pixmap(size.width, size.height);
        QPainter p(&pixmap);
        QBrush brush = p.brush();
        brush.setColor(Qt::gray);
        brush.setStyle(Qt::SolidPattern);
        p.setBrush(brush);
        p.drawRect(5, size.height - size.height / 6 - 5, size.width / progress() * 100 - 5, size.height / 6);
        dockIcon = QIcon(pixmap);
    }
    qApp->setWindowIcon(dockIcon);
}

Q_EXPORT_PLUGIN2(QtMacDockTile, QtMacDockTile)
