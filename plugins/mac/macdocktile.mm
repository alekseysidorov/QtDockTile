#include "macdocktile.h"

#import <AppKit/NSDockTile.h>
#import <Cocoa/Cocoa.h>

extern void qt_mac_set_dock_menu(QMenu *);

//class QtMacDockTile;
//class QtMacDockTilePrivate
//{
//	Q_DECLARE_PUBLIC(QtMacDockTile)
//public:
//	QtMacDockTilePrivate(QtMacDockTile *q) : q_ptr(q) {}
//	QtMacDockTile *q_ptr;
//	//DockIconHandler *dockIconHandler;
//};

QtMacDockTile::QtMacDockTile(QObject *parent) :
	QtDockProvider(parent)/*,
	d_ptr(new QtMacDockTilePrivate(this))*/
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

void QtMacDockTile::setIcon(const QIcon &icon)
{
}

void QtMacDockTile::setOverlayIcon(const QIcon &icon)
{
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

void QtMacDockTile::setProgress(int percents)
{
}

void QtMacDockTile::alert(bool on)
{
	if (on)
		[NSApp requestUserAttention: NSInformationalRequest];
}

Q_EXPORT_PLUGIN2(QtMacDockTile, QtMacDockTile)
