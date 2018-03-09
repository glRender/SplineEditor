#include "ModelKnot.hpp"

ModelKnot::ModelKnot(QObject * parent)
{

}

void ModelKnot::setParam(ModelKnot::Param param, float value)
{

}

float ModelKnot::param(ModelKnot::Param param) const
{
    return -1;
}

void ModelKnot::setPosition(const QVector3D & pos)
{
    m_position = pos;
}

QVector3D ModelKnot::position() const
{
    return m_position;
}

