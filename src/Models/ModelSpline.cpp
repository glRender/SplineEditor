#include "ModelSpline.hpp"
#include <QDebug>

ModelSpline::ModelSpline(QObject * parent)
{
    add({-1,0,-1});
    add({ 0,0,-1});
    add({ -0.33,1.38,-0.95});
    add({ 2,1.5,-1});
    add({ 3, 2.4,-1});
    add({ 3.5,-0.5,-1});
    add({ 1.5,-1.5,-1});

}

bool ModelSpline::availabilityToAdd(QVector3D position) const
{
    return false;
}

bool ModelSpline::add(QVector3D position)
{
    ModelKnot * modelKnot = new ModelKnot();
    modelKnot->setPosition(position);
    modelKnot->setParam(ModelKnot::Param::Continuity, 0.05f);
    modelKnot->setParam(ModelKnot::Param::Bias, 0.7f);
    modelKnot->setParam(ModelKnot::Param::Tension, 0.1f);

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

QList<ModelKnot *> ModelSpline::knotModels() const
{
    return m_knots;
}

uint ModelSpline::size() const
{
    return m_knots.size();
}

const ModelKnot * ModelSpline::at(uint index) const
{
    if (index >=0 and index < (uint)m_knots.size())
    {
        return m_knots[index];
    }
    else
    {
        return nullptr;
    }
}

bool ModelSpline::remove(ModelKnot * knot)
{
    m_knots.removeOne(knot);
    emit removed(knot);
    delete knot;
    return true;
}
