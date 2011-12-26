#include "temporaryicon.h"
#include <QFile>
#include <QImage>
#include <QApplication>
#include <QStyle>
#include <QUuid>
#include <QDesktopServices>

TemporaryIcon::TemporaryIcon(const QIcon &icon)
{
	int size = qApp->style()->pixelMetric(QStyle::PM_ListViewIconSize);
	m_iconSize = QSize(size, size);
	QImage image = icon.pixmap(m_iconSize).toImage();
	if (!image.isNull()) {
		QString name = QUuid::createUuid().toString();
		QString path = QDesktopServices::storageLocation(QDesktopServices::TempLocation);
		m_filePath = path + QLatin1String("/") + name + QLatin1String(".ico");
		image.save(m_filePath, "ico");
	}
}

TemporaryIcon::~TemporaryIcon()
{
	if (!m_filePath.isNull())
		QFile::remove(m_filePath);
}

QString TemporaryIcon::filePath() const
{
	return m_filePath;
}
