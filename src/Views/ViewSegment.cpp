#include "ViewSegment.hpp"

#include "ModelKnot.hpp"
#include "ViewLine.hpp"

ViewSegment::ViewSegment(ModelKnot * mk0, ModelKnot * mk1, ModelKnot * mk2, ModelSplineEditor * modelSplineEditor)
    : m_mk0(mk0)
    , m_mk1(mk1)
    , m_mk2(mk2)
{
    m_line = new ViewLine(mk1->glRenderVec3Position(),
                          mk2->glRenderVec3Position(),
                          1.0,
                          Vec3(1.0f, 0.0f, 1.0f));

    m_mk0PositionChangedConnection = QObject::connect(mk1, &ModelKnot::positionChanged, [this](const ModelKnot * model) {
        m_line->setPointPosition(ViewLine::Points::FirstPoint, model->glRenderVec3Position());
    });

    m_mk2PositionChangedConnection = QObject::connect(mk2, &ModelKnot::positionChanged, [this](const ModelKnot * model) {
        m_line->setPointPosition(ViewLine::Points::LastPoint, model->glRenderVec3Position());
    });

    add(m_line);
}

ViewSegment::~ViewSegment()
{
    QObject::disconnect(m_mk0PositionChangedConnection);
    QObject::disconnect(m_mk2PositionChangedConnection);
}

void ViewSegment::draw(Camera *)
{

}
