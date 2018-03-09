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
    ModelKnot * knot = new ModelKnot();
    knot->setPosition(position);

    m_knots.append(knot);

    emit added(knot);

    Result<bool> res = {true, ""};
    return res;
}

QList<ModelKnot*> ModelSpline::knotModels() const
{
    return m_knots;
}

Result<bool> ModelSpline::remove(QSharedPointer<ModelKnot> knot)
{
    Result<bool> res = {false, ""};
    return res;
}
