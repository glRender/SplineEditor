#pragma once

#include <QObject>
#include <QVector3D>

#include "ModelKnot.hpp"

class ModelSpline : public QObject
{
    Q_OBJECT
public:
    ModelSpline(QObject * parent = nullptr);

    bool add(QVector3D position);
    bool remove(ModelKnot * knot);
    bool availabilityToAdd(QVector3D position) const;
    const ModelKnot * at(uint index) const;
    QList<ModelKnot *> knotModels() const;
    uint size() const;

signals:
    void added(ModelKnot *);
    void removed(ModelKnot *);
    void selectionChanged(ModelKnot *, bool);

private:
    ModelKnot * m_selectedKnot = nullptr;
    QList<ModelKnot*> m_knots;
};
