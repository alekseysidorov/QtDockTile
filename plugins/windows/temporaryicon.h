#ifndef TEMPORARYICON_H
#define TEMPORARYICON_H
#include <QIcon>

class TemporaryIcon
{
public:
	TemporaryIcon(const QIcon &icon);
	~TemporaryIcon();
	QString filePath() const;
private:
	QSize m_iconSize;
	QString m_filePath;
};

#endif // TEMPORARYICON_H
