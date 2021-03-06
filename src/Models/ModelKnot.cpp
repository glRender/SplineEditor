#include "ModelKnot.hpp"

#include <QDebug>

ModelKnot::ModelKnot(QObject * parent)
{
}

void ModelKnot::setParam(ModelKnot::Param param, float value)
{
    m_paramValue[param] = value;
    emit paramsChanged(this);
}

float ModelKnot::param(ModelKnot::Param param) const
{
    return m_paramValue[param];
}

void ModelKnot::setPosition(const QVector3D & pos)
{
    m_position = pos;
    emit positionChanged(this);
}

QVector3D ModelKnot::position() const
{
    return m_position;
}

glRender::Vec3 ModelKnot::positionGlRenderVec3() const
{
    return {m_position.x(), m_position.y(), m_position.z()};
}

void ModelKnot::setSelected(bool selected)
{
    if (m_selected != selected)
    {
        m_selected = selected;
        emit selectionChanged(m_selected);
    }
}

bool ModelKnot::isSelected() const
{
    return m_selected;
}
