#include "ModelSplineEditor.hpp"

ModelSplineEditor::ModelSplineEditor(QObject *parent)
    : QObject(parent)
{
    m_modelEditorMode = new EditorModeMachine(this);
    m_modelSpline = new ModelSpline(this);

    m_modelSpline->add({1,1,-1});
    m_modelSpline->add({2,1,2});

    QVector3D startPoint(-1.0, 0.0, -5.0);
    for (int i=0; i<10; i++)
    {
        m_modelSpline->add(startPoint);
        startPoint += QVector3D(0.2,0.0,0.0);
    }
}

ModelSpline * ModelSplineEditor::modelSpline() const
{
    return m_modelSpline;
}

void ModelSplineEditor::setMode(EditorModeMachine::Mode mode)
{
    m_modelEditorMode->setMode(mode);
}

EditorModeMachine::Mode ModelSplineEditor::mode() const
{
    return m_modelEditorMode->mode();
}
