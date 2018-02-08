#pragma once

#include <QObject>
#include <QVector3D>
#include <QSharedPointer>

#include "utils.h"

class KnotModel : public QObject
{
    Q_OBJECT
public:
    enum class Param
    {
        Radius
    };

    KnotModel(QObject * parent = nullptr);

    void setPosition(const QVector3D & pos);
    QVector3D position() const;

    void setParam(KnotModel::Param param, float value);
    float param(KnotModel::Param param) const;

signals:
    void changed();

private:
    QVector3D m_position;
};
