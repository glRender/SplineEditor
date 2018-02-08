#include "SplineModel.hpp"

SplineModel::SplineModel(QObject *parent)
{
}

Result<bool> SplineModel::availabilityToAdd(QVector3D position) const
{
    Result<bool> res = {false, ""};
    return res;

}

Result<bool> SplineModel::add(QVector3D position)
{
    QSharedPointer<KnotModel> knot = QSharedPointer<KnotModel>::create();
    knot->setPosition(position);

    m_knots.append(knot);

    emit added(knot);

    Result<bool> res = {true, ""};
    return res;
}

Result<QList<QSharedPointer<KnotModel> > > SplineModel::knots() const
{
    Result<QList<QSharedPointer<KnotModel>>> res = {m_knots, ""};
    return res;

}

Result<bool> SplineModel::remove(QSharedPointer<KnotModel> knot)
{
    Result<bool> res = {false, ""};
    return res;
}
