#include "ViewPolylineEditor.h"
#include "ui_mainwindow.h"

#include <QActionGroup>

#include "SplineModel.hpp"
#include "ModelPolylineEditor.h"

ViewPolylineEditor::ViewPolylineEditor(ModelPolylineEditor * model, QWidget * parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_model(model)
{
    ui->setupUi(this);

    ui->viewPolylineArea->setModel(m_model->model);

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

ViewPolylineEditor::~ViewPolylineEditor()
{
    delete ui;
}
