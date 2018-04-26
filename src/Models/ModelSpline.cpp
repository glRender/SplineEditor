#include "ModelSpline.hpp"
#include <QDebug>

ModelSpline::ModelSpline(QObject * parent)
{
    add({-1,0,-1});
    add({ 0,0,-1});
    add({ 1,0.5,-1});
    add({ 2,1.5,-1});

}

Result<bool> ModelSpline::availabilityToAdd(QVector3D position) const
{
    Result<bool> res = {false, ""};
    return res;

}

Result<bool> ModelSpline::add(QVector3D position)
{
    ModelKnot * modelKnot = new ModelKnot();
    modelKnot->setPosition(position);
    m_knots.append(modelKnot);

    emit added(modelKnot);

    Result<bool> res = {true, ""};
    return res;
}

void ModelSpline::setKnotSelected(ModelKnot * modelKnot)
{
    if (m_selectedKnot != nullptr)
    {
        emit loseSelection(m_selectedKnot);
    }
    m_selectedKnot = modelKnot;
    emit newSelection(modelKnot);

}

bool ModelSpline::isKnotSelected(ModelKnot * model) const
{
    return model == m_selectedKnot;
}

std::pair<ModelKnot *, ModelKnot *> ModelSpline::neighbors(ModelKnot * modelKnot) const
{
    ModelKnot * mkLeft = nullptr;
    ModelKnot * mkRigth = nullptr;

    auto index = m_knots.indexOf(modelKnot);
    if (index != -1)
    {

        if (index-1 >= 0)
        {
            mkLeft = m_knots.value(index-1);
        }
        if (index+1 < m_knots.size())
        {
            mkRigth = m_knots.value(index+1);
        }

    }
    return {mkLeft, mkRigth};
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
