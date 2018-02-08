#include "KnotModel.hpp"

KnotModel::KnotModel(QObject * parent)
{

}

void KnotModel::setParam(KnotModel::Param param, float value)
{

}

float KnotModel::param(KnotModel::Param param) const
{
    return -1;
}

void KnotModel::setPosition(const QVector3D & pos)
{
    m_position = pos;
}

QVector3D KnotModel::position() const
{
    return m_position;
}

