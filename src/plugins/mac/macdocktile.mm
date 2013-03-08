/**************************************************************************
**
**  macdocktile.h
**
** Copyright (c) 2011 Nokia Corporation and/or its subsidiary(-ies).
**
** Contact: Nokia Corporation (qt-info@nokia.com)
**
**
** GNU Lesser General Public License Usage
**
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this file.
** Please review the following information to ensure the GNU Lesser General
** Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** Other Usage
**
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
**************************************************************************/

#include "macdocktile.h"

#import <AppKit/NSDockTile.h>
#import <AppKit/NSApplication.h>
#import <AppKit/NSImageView.h>
#import <AppKit/NSCIImageRep.h>
#import <AppKit/NSBezierPath.h>
#import <AppKit/NSColor.h>
#import <Foundation/NSString.h>

#include <QApplication>
#include <QIcon>
#include <QPainter>
#include <QtPlugin>
#include <QDebug>

extern void qt_mac_set_dock_menu(QMenu *);

@interface ApplicationProgressView : NSView {
    int min;
    int max;
    int value;
}

+ (ApplicationProgressView *)sharedProgressView;

- (void)setRangeMin:(int)v1 max:(int)v2;
- (void)setValue:(int)v;
- (void)updateBadge;

@end

static ApplicationProgressView *sharedProgressView = nil;

@implementation ApplicationProgressView

+ (ApplicationProgressView *)sharedProgressView
{
    if (sharedProgressView == nil) {
        sharedProgressView = [[ApplicationProgressView alloc] init];
    }
    return sharedProgressView;
}

- (void)setRangeMin:(int)v1 max:(int)v2
{
    min = v1;
    max = v2;
    [self updateBadge];
}

- (void)setValue:(int)v
{
    value = v;
    [self updateBadge];
}

- (void)updateBadge
{
    [[NSApp dockTile] display];
}

- (void)drawRect:(NSRect)rect
{
    Q_UNUSED(rect)
    NSRect boundary = [self bounds];
    [[NSApp applicationIconImage] drawInRect:boundary
        fromRect:NSZeroRect
        operation:NSCompositeCopy
        fraction:1.0];
    NSRect progressBoundary = boundary;
    progressBoundary.size.height *= 0.13;
    progressBoundary.size.width *= 0.8;
    progressBoundary.origin.x = (NSWidth(boundary) - NSWidth(progressBoundary))/2.;
    progressBoundary.origin.y = NSHeight(boundary)*0.13;

    double range = max - min;
    double percent = 0.50;
    if (range != 0)
        percent = (value - min) / range;
    if (percent > 1)
        percent = 1;
    else if (percent < 0)
        percent = 0;

    NSRect currentProgress = progressBoundary;
    currentProgress.size.width *= percent;
    [[NSColor blackColor] setFill];
    [NSBezierPath fillRect:progressBoundary];
    [[NSColor lightGrayColor] setFill];
    [NSBezierPath fillRect:currentProgress];
    [[NSColor blackColor] setStroke];
    [NSBezierPath strokeRect:progressBoundary];
}

@end


QtMacDockTile::QtMacDockTile(QObject *parent) :
    QtDockProvider(parent),
    m_isAlert(false)
{
    qDebug("%s", Q_FUNC_INFO);
    [[ApplicationProgressView sharedProgressView] setRangeMin:0 max:100];
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

void QtMacDockTile::setBadge(const QString &badge)
{
    NSString *cocoaString = [[NSString alloc] initWithUTF8String:badge.toUtf8().constData()];
    [[NSApp dockTile] setBadgeLabel:cocoaString];
    [[NSApp dockTile] setShowsApplicationBadge:true];
    [cocoaString release];
}

void QtMacDockTile::clearBadge()
{
    setBadge(QString());
    [[NSApp dockTile] setShowsApplicationBadge:false];
}

void QtMacDockTile::setProgress(int value)
{
    [[ApplicationProgressView sharedProgressView] setValue:value];
    if (value) {
        [[NSApp dockTile] setContentView:[ApplicationProgressView sharedProgressView]];
    } else {
        [[NSApp dockTile] setContentView:nil];
    }
    [[NSApp dockTile] display];
}

void QtMacDockTile::alert(bool on)
{
    m_isAlert = on;
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    if (on) {
        [[NSApplication sharedApplication] requestUserAttention:NSInformationalRequest];
    } else {
        [[NSApplication sharedApplication] cancelUserAttentionRequest:NSInformationalRequest];
    }
    [pool release];
}


#if (QT_VERSION < QT_VERSION_CHECK(5, 0, 0))
Q_EXPORT_PLUGIN2(QtMacDockTile, QtMacDockTile)
#endif
