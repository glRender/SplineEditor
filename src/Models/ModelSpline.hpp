#pragma once

#include <QObject>
#include <QVector3D>
#include <QSharedPointer>

#include "Result.hpp"
#include "ModelKnot.hpp"
#include "EditorModeMachine.hpp"

class ModelSpline : public QObject
{
    Q_OBJECT
public:
    ModelSpline(QObject * parent = nullptr);

    Result<bool> availabilityToAdd(QVector3D position) const;
    Result<bool> add(QVector3D position);
    Result<QList<QSharedPointer<ModelKnot>>> knots() const;
    Result<bool> remove(QSharedPointer<ModelKnot> knot);

signals:
    void changed(QSharedPointer<ModelKnot>);
    void added(QSharedPointer<ModelKnot>);
    void removed(QSharedPointer<ModelKnot>);

private:
    QList<QSharedPointer<ModelKnot>> m_knots;
};
