#include "ModelSplineEditor.hpp"

ModelSplineEditor::ModelSplineEditor(ModelSpline * modelSpline, QObject *parent)
    : QObject(parent)
    , m_modelSpline(modelSpline)
{
}

void ModelSplineEditor::setMode(ModelSplineEditor::Mode mode)
{
    m_mode = mode;
}

ModelSplineEditor::Mode ModelSplineEditor::mode() const
{
    return m_mode;
}

ModelSpline * ModelSplineEditor::modelSpline() const
{
    return m_modelSpline;
}
