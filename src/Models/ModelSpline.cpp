#include "ModelSpline.hpp"
#include <QDebug>

ModelSpline::ModelSpline(QObject * parent)
{
    add({-1,0,-1});
    add({ 0,0,-1});
    add({ -0.33,1.38,-0.95});
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

QList<ModelKnot *> ModelSpline::knotModels() const
{
    return m_knots;
}

ModelKnot * ModelSpline::knotFromEnd(uint offset) const
{
    return knotFromKnot(m_knots.last(), offset);
}

ModelKnot * ModelSpline::knotFromKnot(ModelKnot * knot,  uint offset) const
{
    int argKnotIndex = m_knots.indexOf(knot);
    if (argKnotIndex == -1)
    {
        return nullptr;
    }

    int index = argKnotIndex - offset;
    if (index >= 0 and index <= argKnotIndex)
    {
        return m_knots.at(index);
    }
    else
    {
        return nullptr;
    }
}

uint ModelSpline::knotIndex(ModelKnot * modelKnot) const
{
    return m_knots.indexOf(modelKnot);
}

uint ModelSpline::size() const
{
    return m_knots.size();
}

Result<bool> ModelSpline::remove(ModelKnot * knot)
{
    m_knots.removeOne(knot);
    emit removed(knot);

    Result<bool> res = {false, ""};
    return res;
}
