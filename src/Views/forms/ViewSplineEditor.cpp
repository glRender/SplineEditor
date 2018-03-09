#include "ViewSplineEditor.hpp"
#include "ui_ViewSplineEditor.h"

#include <QActionGroup>

#include "ModelSplineEditor.hpp"
#include "ModelSpline.hpp"

#include "ControllerSplineEditor.hpp"
#include "ControllerSpline.hpp"

ViewSplineEditor::ViewSplineEditor(ModelSplineEditor * model, ControllerSplineEditor * controller, QWidget * parent)
    : QMainWindow(parent)
    , ui(new Ui::ViewSplineEditor)
    , m_model(model)
    , m_controller(controller)
{
    ui->setupUi(this);

//    ui->splineArea->setModel(m_model->modelSpline());
    ui->splineArea->setController(m_controller->controllerSpline());

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
