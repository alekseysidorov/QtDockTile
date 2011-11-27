#ifndef QTDOCKICON_P_H
#define QTDOCKICON_P_H
#include "qtdockicon.h"
#include <QIcon>

class QtDockIcon;
class QtDockIconPrivate
{
	Q_DECLARE_PUBLIC(QtDockIcon)
public:
	QtDockIconPrivate(QtDockIcon *q) : q_ptr(q) {}
	QtDockIcon *q_ptr;
};


#endif // QTDOCKICON_P_H
