#pragma once

#include <QObject>
#include <QVector3D>
#include <QMap>

#include <glRender.h>

class ModelKnot : public QObject
{
    Q_OBJECT
public:
    enum class Param
    {
        Radius
    };

    ModelKnot(QObject * parent = nullptr);

    void setPosition(const QVector3D & pos);
    QVector3D position() const;
    glRender::Vec3 glRenderVec3Position() const;

    void setParam(ModelKnot::Param, float);
    float param(ModelKnot::Param) const;

signals:
    void positionChanged(const ModelKnot *);

private:
    QVector3D m_position;
    QMap<ModelKnot::Param, float> m_paramValue;
};
