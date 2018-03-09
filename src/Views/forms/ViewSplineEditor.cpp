#include "ViewSplineEditor.hpp"
#include "ui_ViewSplineEditor.h"

#include <QActionGroup>

#include "ModelSpline.hpp"
#include "ModelSplineEditor.hpp"

ViewSplineEditor::ViewSplineEditor(ModelSplineEditor * model, QWidget * parent)
    : QMainWindow(parent)
    , ui(new Ui::ViewSplineEditor)
    , m_model(model)
{
    ui->setupUi(this);

    ui->splineArea->setModel(m_model->modelSpline());

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

ViewSplineEditor::~ViewSplineEditor()
{
    delete ui;
}
