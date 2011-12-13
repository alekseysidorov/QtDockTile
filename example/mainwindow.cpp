#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qtdocktile.h>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	m_tile(new QtDockTile(this))
{
	ui->setupUi(this);
#if defined(Q_OS_UNIX) || !defined(Q_OS_MACOSX)
	ui->actionElementWithIcon->setIcon(QIcon::fromTheme("applications-internet"));
#endif

	m_tile->setMenu(ui->menu);
	connect(ui->pushButton, SIGNAL(clicked(bool)), m_tile, SLOT(alert(bool)));
	connect(ui->lineEdit, SIGNAL(textChanged(QString)), m_tile, SLOT(setBadge(QString)));
}

MainWindow::~MainWindow()
{
	delete ui;
}
