#pragma once

#include <QObject>
#include <QVector3D>
#include <QSharedPointer>

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

    void setParam(ModelKnot::Param param, float value);
    float param(ModelKnot::Param param) const;

signals:
    void changed();

private:
    QVector3D m_position;
};
