#pragma once

#include <QObject>
#include <QVector3D>

#include "Result.hpp"
#include "ModelKnot.hpp"

class ModelSpline : public QObject
{
    Q_OBJECT
public:
    ModelSpline(QObject * parent = nullptr);

    Result<bool> availabilityToAdd(QVector3D position) const;
    Result<bool> add(QVector3D position);

    void setKnotSelected(ModelKnot *);
    bool isKnotSelected(ModelKnot *) const;

    std::pair<ModelKnot*, ModelKnot*> neighbors(ModelKnot*) const;

    QList<ModelKnot *> knotModels() const;
    ModelKnot * knotFromEnd(uint offset) const;
    ModelKnot * knotFromKnot(ModelKnot *, uint offset) const;
    uint knotIndex(ModelKnot *) const;
    uint size() const;

    Result<bool> remove(ModelKnot * knot);

signals:
    void added(ModelKnot *);
    void removed(ModelKnot *);
    void newSelection(ModelKnot *);
    void loseSelection(ModelKnot *);

private:
    ModelKnot * m_selectedKnot = nullptr;
    QList<ModelKnot*> m_knots;
};
