#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "SplineModel.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    ui->mainToolBar->addAction(ui->actionNew);
//    ui->mainToolBar->addAction(ui->actionJSON);
//    ui->mainToolBar->addAction(ui->actionExit);

//    addAction(ui->actionExit);
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
