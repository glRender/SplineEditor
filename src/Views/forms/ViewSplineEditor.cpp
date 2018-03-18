#include "ViewSplineEditor.hpp"
#include "ui_ViewSplineEditor.h"

#include <QActionGroup>

#include "ModelSplineEditor.hpp"
#include "ModelSpline.hpp"

ViewSplineEditor::ViewSplineEditor(ModelSplineEditor * modelEditor, QWidget * parent)
    : QMainWindow(parent)
    , ui(new Ui::ViewSplineEditor)
    , m_modelEditor(modelEditor)
{
    ui->setupUi(this);

    ui->splineArea->setModel(m_modelEditor);

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
            m_modelEditor->setMode(ModelSplineEditor::Mode::Deletion);
        }
        else if (action == ui->actionSelectMark)
        {
            m_modelEditor->setMode(ModelSplineEditor::Mode::Selection);
        }

    });

    if (m_modelEditor->mode() == ModelSplineEditor::Mode::Selection)
    {
        ui->actionSelectMark->trigger();
    }
    else if (m_modelEditor->mode() == ModelSplineEditor::Mode::Addition)
    {
        ui->actionAddMark->trigger();
    }
    else if (m_modelEditor->mode() == ModelSplineEditor::Mode::Moving)
    {
        ui->actionMoveMark->trigger();
    }
    else if (m_modelEditor->mode() == ModelSplineEditor::Mode::Deletion)
    {
        ui->actionRemoveMark->trigger();
    }

}

ViewSplineEditor::~ViewSplineEditor()
{
    delete ui;
}
