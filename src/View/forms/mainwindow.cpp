#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QActionGroup>

#include "SplineModel.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QActionGroup * mouseMarkSelection = new QActionGroup(this);
    mouseMarkSelection->setExclusive(true);
    mouseMarkSelection->addAction(ui->actionSelectMark);
    mouseMarkSelection->addAction(ui->actionAddMark);
    mouseMarkSelection->addAction(ui->actionMoveMark);
    mouseMarkSelection->addAction(ui->actionRemoveMark);

    ui->mainToolBar->addActions(mouseMarkSelection->actions());

    addAction(ui->actionExit);
//    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::exitEffort);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setModel(QSharedPointer<SplineModel> model)
{
    m_model = model;
    ui->polylineArea->setModel(model);
}
