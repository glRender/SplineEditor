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
        Tension,
        Continuity,
        Bias
    };

    ModelKnot(QObject * parent = nullptr);

    void setPosition(const QVector3D & pos);
    QVector3D position() const;
    glRender::Vec3 glRenderVec3Position() const;

    void setSelected(bool selected);
    bool isSelected() const;

    void setParam(ModelKnot::Param, float);
    float param(ModelKnot::Param) const;

signals:
    void positionChanged(const ModelKnot *);
    void paramsChanged(const ModelKnot *);
    void selectionChanged(bool);

private:
    QVector3D m_position;
    QMap<ModelKnot::Param, float> m_paramValue;
    bool m_selected = false;
};
