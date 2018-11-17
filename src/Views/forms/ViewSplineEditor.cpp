#include "ViewSplineEditor.hpp"
#include "ui_ViewSplineEditor.h"

#include <QActionGroup>

#include "ModelSpline.hpp"
#include "ModelSplineEditor.hpp"

ViewSplineEditor::ViewSplineEditor(ModelSplineEditor * modelEditor,
                                   QWidget * parent)
    : QMainWindow(parent)
    , ui(new Ui::ViewSplineEditor)
    , m_modelEditor(modelEditor)
{
    ui->setupUi(this);

    ui->splineArea->setModel(m_modelEditor);
    ui->knotParams->setModel(m_modelEditor);

    QActionGroup * mouseMarkSelection = new QActionGroup(this);
    mouseMarkSelection->setExclusive(true);
    mouseMarkSelection->addAction(ui->actionSelectKnot);
    mouseMarkSelection->addAction(ui->actionAddKnot);
    mouseMarkSelection->addAction(ui->actionMoveKnot);
    mouseMarkSelection->addAction(ui->actionRemoveKnot);

    ui->mainToolBar->addActions(mouseMarkSelection->actions());

    addAction(ui->actionExit);

    connect(mouseMarkSelection, &QActionGroup::triggered, this,
            [this](QAction * action) {
                if (action == ui->actionSelectKnot)
                {
                    m_modelEditor->setMode(ModelSplineEditor::Mode::Selection);
                }
                else if (action == ui->actionAddKnot)
                {
                    m_modelEditor->setMode(ModelSplineEditor::Mode::Addition);
                }
                else if (action == ui->actionMoveKnot)
                {
                    m_modelEditor->setMode(ModelSplineEditor::Mode::Moving);
                }
                else if (action == ui->actionRemoveKnot)
                {
                    m_modelEditor->setMode(ModelSplineEditor::Mode::Removing);
                }
            });

    if (m_modelEditor->mode() == ModelSplineEditor::Mode::Selection)
    {
        ui->actionSelectKnot->trigger();
    }
    else if (m_modelEditor->mode() == ModelSplineEditor::Mode::Addition)
    {
        ui->actionAddKnot->trigger();
    }
    else if (m_modelEditor->mode() == ModelSplineEditor::Mode::Moving)
    {
        ui->actionMoveKnot->trigger();
    }
    else if (m_modelEditor->mode() == ModelSplineEditor::Mode::Removing)
    {
        ui->actionRemoveKnot->trigger();
    }
}

ViewSplineEditor::~ViewSplineEditor()
{
    delete ui;
}
