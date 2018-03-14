#include "ViewSplineEditor.hpp"
#include "ui_ViewSplineEditor.h"

#include <QActionGroup>

#include "ModelSplineEditor.hpp"
#include "ModelSpline.hpp"

#include "ControllerSplineEditor.hpp"
#include "ControllerSpline.hpp"

ViewSplineEditor::ViewSplineEditor(ControllerSplineEditor * controllerSplineEditor, ControllerSpline * controllerSpline, QWidget * parent)
    : QMainWindow(parent)
    , ui(new Ui::ViewSplineEditor)
    , m_controllerSplineEditor(controllerSplineEditor)
    , m_controllerSpline(controllerSpline)
{
    ui->setupUi(this);

    ui->splineArea->setControllerSpline(m_controllerSpline);

    QActionGroup * mouseMarkSelection = new QActionGroup(this);
    mouseMarkSelection->setExclusive(true);
    mouseMarkSelection->addAction(ui->actionSelectMark);
    mouseMarkSelection->addAction(ui->actionAddMark);
    mouseMarkSelection->addAction(ui->actionMoveMark);
    mouseMarkSelection->addAction(ui->actionRemoveMark);

    ui->mainToolBar->addActions(mouseMarkSelection->actions());

    addAction(ui->actionExit);

    connect(mouseMarkSelection, &QActionGroup::triggered, this, [this](QAction * action) {
        if (action == ui->actionRemoveMark)
        {
            m_controllerSplineEditor->setMode(EditorModeMachine::Mode::Deletion);
        }
    });

}

ViewSplineEditor::~ViewSplineEditor()
{
    delete ui;
}
