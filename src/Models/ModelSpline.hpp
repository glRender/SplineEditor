#pragma once

#include <QObject>
#include <QVector3D>

#include "ModelKnot.hpp"

class ModelSpline : public QObject
{
    Q_OBJECT
public:
    ModelSpline(QObject * parent = nullptr);

    bool availabilityToAdd(QVector3D position) const;
    bool add(QVector3D position);

    std::pair<ModelKnot*, ModelKnot*> neighbors(ModelKnot*) const;

    QList<ModelKnot *> knotModels() const;
    ModelKnot * knotFromEnd(uint offset) const;
    ModelKnot * knotFromKnot(ModelKnot *, uint offset) const;
    uint knotIndex(ModelKnot *) const;
    uint size() const;
    bool remove(ModelKnot * knot);
    const ModelKnot * at(uint index) const;

signals:
    void added(ModelKnot *);
    void removed(ModelKnot *);
    void selectionChanged(ModelKnot *, bool);

private:
    ModelKnot * m_selectedKnot = nullptr;
    QList<ModelKnot*> m_knots;
};
