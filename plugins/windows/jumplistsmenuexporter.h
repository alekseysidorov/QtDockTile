#ifndef JUMPLISTSMENUEXPORTER_H
#define JUMPLISTSMENUEXPORTER_H

#include <QObject>

class QMenu;
class JumpListsMenuExporterPrivate;
class JumpListsMenuExporter : public QObject
{
	Q_OBJECT
	Q_DECLARE_PRIVATE(JumpListsMenuExporter)
public:
	explicit JumpListsMenuExporter(QMenu *menu = 0);
	~JumpListsMenuExporter();
	void setMenu(QMenu *menu);
	QMenu *menu() const;
protected:
	bool eventFilter(QObject *, QEvent *);
	QScopedPointer<JumpListsMenuExporterPrivate> d_ptr;
};

#endif // JUMPLISTSMENUEXPORTER_H
