#include "ModelSplineEditor.hpp"

ModelSplineEditor::ModelSplineEditor(QObject *parent)
    : QObject(parent)
{
    m_modelEditorMode = new EditorModeMachine(this);
}

//ModelSpline * ModelSplineEditor::modelSpline() const
//{
//    return m_modelSpline;
//}

void ModelSplineEditor::setMode(EditorModeMachine::Mode mode)
{
    m_modelEditorMode->setMode(mode);
}

EditorModeMachine::Mode ModelSplineEditor::mode() const
{
    return m_modelEditorMode->mode();
}
