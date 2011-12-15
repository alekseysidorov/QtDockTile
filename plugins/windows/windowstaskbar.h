#ifndef WINDOWSTASKBAR_H
#define WINDOWSTASKBAR_H
#include <qtdockprovider.h>
#include <QWidget>

class WindowsTaskBar : public QtDockProvider
{
	Q_OBJECT
	Q_INTERFACES(QtDockProvider)
public:
	explicit WindowsTaskBar(QObject *parent = 0);
	virtual ~WindowsTaskBar();
	virtual bool isUsable() const;
	virtual void setMenu(QMenu *menu);
	virtual void setIcon(const QIcon &icon);
	virtual void setBadge(const QString &badge);
	virtual void setProgress(int percents);
	virtual void alert(bool on);
};

#endif // WINDOWSTASKBAR_H
