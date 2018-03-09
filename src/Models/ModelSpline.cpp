#include "ModelSpline.hpp"

ModelSpline::ModelSpline(QObject * parent)
{
}

Result<bool> ModelSpline::availabilityToAdd(QVector3D position) const
{
    Result<bool> res = {false, ""};
    return res;

}

Result<bool> ModelSpline::add(QVector3D position)
{
    QSharedPointer<ModelKnot> knot = QSharedPointer<ModelKnot>::create();
    knot->setPosition(position);

    m_knots.append(knot);

    emit added(knot);

    Result<bool> res = {true, ""};
    return res;
}

Result<QList<QSharedPointer<ModelKnot> > > ModelSpline::knots() const
{
    Result<QList<QSharedPointer<ModelKnot>>> res = {m_knots, ""};
    return res;

}

Result<bool> ModelSpline::remove(QSharedPointer<ModelKnot> knot)
{
    Result<bool> res = {false, ""};
    return res;
}
