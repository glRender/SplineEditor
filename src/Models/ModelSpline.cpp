#include "ModelSpline.hpp"
#include <QDebug>

ModelSpline::ModelSpline(QObject * parent)
{
    add({-1,0,-1});
    add({ 0,0,-1});
    add({ 1,0.5,-1});
//    add({1,1,-1});
//    add({2,1,2});
//    QVector3D startPoint(-1.0, 0.0, -5.0);
//    for (int i=0; i<10; i++)
//    {
//        add(startPoint);
//        startPoint += QVector3D(0.2,0.0,0.0);
//    }
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

Result<bool> ModelSpline::remove(ModelKnot * knot)
{
    m_knots.removeOne(knot);
    emit removed(knot);

    Result<bool> res = {false, ""};
    return res;
}
