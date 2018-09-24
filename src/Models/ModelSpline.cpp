#include "ModelSpline.hpp"
#include <QDebug>

ModelSpline::ModelSpline(QObject * parent)
{
    add({-1,0,-1});
    add({ 0,0,-1});
    add({ -0.33,1.38,-0.95});
    add({ 2,1.5,-1});

}

bool ModelSpline::availabilityToAdd(QVector3D position) const
{
    return false;
}

bool ModelSpline::add(QVector3D position)
{
    ModelKnot * modelKnot = new ModelKnot();
    modelKnot->setPosition(position);

    connect(modelKnot, &ModelKnot::selectionChanged, [this, modelKnot](bool selected) {
        if (selected and m_selectedKnot != modelKnot)
        {
            if (m_selectedKnot != nullptr)
            {
                m_selectedKnot->setSelected(false);
            }
            m_selectedKnot = modelKnot;
        }
        emit selectionChanged(modelKnot, selected);
    });

    m_knots.append(modelKnot);

    emit added(modelKnot);
    return true;
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

bool ModelSpline::remove(ModelKnot * knot)
{
    emit removed(knot);
    m_knots.removeOne(knot);
    return false;
}
