#ifndef QMLBINDING_H
#define QMLBINDING_H
#include <QDeclarativeExtensionPlugin>

class QuickDockTile : public QDeclarativeExtensionPlugin
{
	Q_OBJECT
public:
	QuickDockTile();
	virtual void registerTypes(const char *uri);
};

#endif // QMLBINDING_H
