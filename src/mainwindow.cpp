#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->mainToolBar->addAction(ui->actionNew);
    ui->mainToolBar->addAction(ui->actionJSON);
    ui->mainToolBar->addAction(ui->actionExit);

    addAction(ui->actionExit);

    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::exitEffort);    
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addKnot(Vec3 pos)
{

}

void MainWindow::removeKnot(Vec3 pos)
{

}

void MainWindow::moveKnot(uint knotIndex, Vec3 pos)
{

}

void MainWindow::setKnotParam(uint knotIndex, Knot::Param param, float value)
{

}

void MainWindow::selectKnot(uint knotIndex)
{

}

void MainWindow::deselectKnot()
{

}
