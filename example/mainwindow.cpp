#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qtdocktile.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_tile(new QtDockTile(this))
{
    ui->setupUi(this);
	ui->menubar->setNativeMenuBar(false);

    ui->actionElementWithIcon->setIcon(QIcon::fromTheme("applications-internet"));
	m_tile->setMenu(ui->menu);

    connect(ui->pushButton, SIGNAL(clicked()), m_tile, SLOT(alert()));
    connect(ui->lineEdit, SIGNAL(textChanged(QString)), m_tile, SLOT(setBadge(QString)));
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), m_tile, SLOT(setProgress(int)));

	connect(ui->element, SIGNAL(triggered()), SLOT(actionTriggered()));
	connect(ui->element1, SIGNAL(triggered()), SLOT(actionTriggered()));
	connect(ui->element2, SIGNAL(triggered()), SLOT(actionTriggered()));
	connect(ui->actionElementWithIcon, SIGNAL(triggered()), SLOT(actionTriggered()));
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::actionTriggered() const
{
	QAction *action = static_cast<QAction*>(sender());
	statusBar()->showMessage(tr("Action %1 triggered").arg(action->text()), 2000);
}
