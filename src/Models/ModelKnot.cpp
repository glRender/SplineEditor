#include "ModelKnot.hpp"

ModelKnot::ModelKnot(QObject * parent)
{
    m_paramValue[Param::Radius] = 0.0f;
}

void ModelKnot::setParam(ModelKnot::Param param, float value)
{
    m_paramValue[param] = value;
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

glRender::Vec3 ModelKnot::glRenderVec3Position() const
{
    return {m_position.x(), m_position.y(), m_position.z()};
}

