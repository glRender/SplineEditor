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
    int indexOf(const ModelKnot *) const;
    QList<ModelKnot *> knotModels() const;
    uint size() const;
    QPair<QVector3D, QVector3D> derivative(const ModelKnot *, const ModelKnot *, const ModelKnot *, const ModelKnot *) const;
    QVector3D interpolate(float t, QVector3D p1, QVector3D p2, QVector3D r1, QVector3D r2) const;
    QList<QVector3D> approximateByLines(const float & from, const float & to, const QVector3D & p1, const QVector3D & p2, std::function<QVector3D(float)> f) const;

signals:
    void added(ModelKnot *);
    void removed(ModelKnot *);
    void selectionChanged(ModelKnot *, bool);

private:
    ModelKnot * m_selectedKnot = nullptr;
    QList<ModelKnot*> m_knots;
};
