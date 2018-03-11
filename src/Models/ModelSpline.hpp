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
    QList<ModelKnot*> knotModels() const;
    Result<bool> remove(ModelKnot * knot);

signals:
    void changed(QSharedPointer<ModelKnot>);
    void added(ModelKnot *);
    void removed(ModelKnot *);

private:
    QList<ModelKnot*> m_knots;
};
