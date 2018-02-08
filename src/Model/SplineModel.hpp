#pragma once

#include <QObject>
#include <QVector3D>
#include <QSharedPointer>

#include "Result.hpp"
#include "KnotModel.hpp"

class SplineModel : public QObject
{
    Q_OBJECT
public:
    SplineModel(QObject * parent = nullptr);

    Result<bool> availabilityToAdd(QVector3D position) const;
    Result<bool> add(QVector3D position);
    Result<QList<QSharedPointer<KnotModel>>> knots() const;
    Result<bool> remove(QSharedPointer<KnotModel> knot);

signals:
    void changed(QSharedPointer<KnotModel>);
    void added(QSharedPointer<KnotModel>);
    void removed(QSharedPointer<KnotModel>);

private:
    QList<QSharedPointer<KnotModel>> m_knots;

};
