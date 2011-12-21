#include "windowstaskbar.h"
#include <QSysInfo>
#include <QtPlugin>
#include "wrapper/taskbar.h"
#include <QApplication>
#include <QPainter>
#include <QStyle>
#include "jumplistsmenuexporter.h"

WindowsTaskBar::WindowsTaskBar(QObject *parent) :
	QtDockProvider(parent),
	m_menuExporter(new JumpListsMenuExporter(this))
{
}

WindowsTaskBar::~WindowsTaskBar()
{
}

bool WindowsTaskBar::isUsable() const
{
	return QSysInfo::windowsVersion() >= QSysInfo::WV_WINDOWS7;
}

void WindowsTaskBar::setMenu(QMenu *menu)
{
	m_menuExporter->setMenu(menu);
}

void WindowsTaskBar::setIcon(const QIcon &icon)
{
	qApp->setWindowIcon(icon);
}

void WindowsTaskBar::setBadge(const QString &badge)
{
	if (badge.isEmpty())
		clearOverlayIcon(window()->winId());
	else {
		QPixmap pixmap = createBadge(badge);
		setOverlayIcon(window()->winId(), pixmap.toWinHICON());
	}
}

void WindowsTaskBar::setProgress(int percents)
{
	int progress = qBound(0, percents, 100);
	setProgressValue(window()->winId(), progress);
}

void WindowsTaskBar::alert(bool on)
{
	if (on)
		qApp->alert(window(), 5000);
	else
		qApp->alert(window());
}

QPixmap WindowsTaskBar::createBadge(const QString &badge) const
{
	QPixmap pixmap(overlayIconSize());
	QRect rect = pixmap.rect();
	rect.adjust(1, 1, -1, -1);
	pixmap.fill(Qt::transparent);

	QPainter painter(&pixmap);
	painter.setRenderHint(QPainter::Antialiasing);
	QPalette palette = window()->palette();

	painter.setBrush(palette.toolTipBase());

	QPen pen = painter.pen();
	pen.setColor(palette.color(QPalette::ToolTipText));
	painter.setPen(pen);

	//QFont font = painter.font();
	//font.setPointSizeF(font.pointSizeF() * 0.8);
	//painter.setFont(font);

	QString label = QFontMetrics(painter.font()).elidedText(badge, Qt::ElideMiddle, rect.width());
	painter.drawRoundedRect(rect, 5, 5);
	painter.drawText(rect,
					 Qt::AlignCenter | Qt::TextSingleLine,
					 label);
	return pixmap;
}

QSize WindowsTaskBar::overlayIconSize() const
{
	int size = qApp->style()->pixelMetric(QStyle::PM_ListViewIconSize);
	return QSize(size, size);
}

Q_EXPORT_PLUGIN2(WindowsTaskBar, WindowsTaskBar)
