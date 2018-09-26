#include "ViewSegment.hpp"

#include <QDebug>

#include "ModelKnot.hpp"
#include "ViewLine.hpp"

ViewSegment::ViewSegment(const ModelKnot * mk0, const ModelKnot * mk1, const ModelKnot * mk2, const ModelKnot * mk3)
{
//    Q_CHECK_PTR(mk0);
    Q_CHECK_PTR(mk1);
    Q_CHECK_PTR(mk2);
    Q_CHECK_PTR(mk3);

    float tension = mk1->param(ModelKnot::Param::Tension);
    float continuity = mk1->param(ModelKnot::Param::Continuity);
    float bias = mk1->param(ModelKnot::Param::Bias);

    Vec3 r1 = 0.5f*(1-tension)*((1+bias)*(1-continuity)*(mk1->positionGlRenderVec3()-mk0->positionGlRenderVec3())+ (1-bias)*(1+continuity)*(mk2->positionGlRenderVec3()-mk1->positionGlRenderVec3()));

    tension = mk2->param(ModelKnot::Param::Tension);
    continuity = mk2->param(ModelKnot::Param::Continuity);
    bias = mk2->param(ModelKnot::Param::Bias);

    Vec3 r2 = 0.5f*(1-tension)*((1+bias)*(1+continuity)*(mk2->positionGlRenderVec3()-mk1->positionGlRenderVec3())+ (1-bias)*(1-continuity)*(mk3->positionGlRenderVec3()-mk2->positionGlRenderVec3()));

    QList<Vec3> points;

    float t = 0;
    const uint segmentsNumber = 50;
    for (uint i=0; i<=segmentsNumber; i++)
    {
        t = (float)i / (float)segmentsNumber;
//        t1 = (float)i+1 / (float)segmentsNumber;
//        t = ease(t, 0.0, 1.0);
        Vec3 p0 = interpolate(t, mk1->positionGlRenderVec3(), mk2->positionGlRenderVec3(), r1, r2);
        points.append(p0);
    }

    for(uint i=1; i<points.size(); i++)
    {
        m_line = new ViewLine(points[i-1],
                              points[i],
                              1.0,
                              m_normalColor);
        add(m_line);
    }

    setFirst(mk0);
    setSecond(mk1);
    setThird(mk2);

    add(m_line);
}

ViewSegment::~ViewSegment()
{
    QObject::disconnect(m_mk0PositionChangedConnection);
    QObject::disconnect(m_mk1PositionChangedConnection);
    QObject::disconnect(m_mk2PositionChangedConnection);
    Node::remove(m_line);
}

void ViewSegment::setFirst(const ModelKnot * modelKnot)
{
    //Q_CHECK_PTR(modelKnot);
    m_mk0 = modelKnot;
    QObject::disconnect(m_mk0PositionChangedConnection);

    if (modelKnot)
    {
        m_mk0PositionChangedConnection = QObject::connect(modelKnot, &ModelKnot::positionChanged, [this](const ModelKnot * model) {
        });
    }

}

void ViewSegment::setSecond(const ModelKnot * modelKnot)
{
    Q_CHECK_PTR(modelKnot);
    m_mk1 = modelKnot;
    QObject::disconnect(m_mk1PositionChangedConnection);

    if (modelKnot)
    {
//        m_line->setPointPosition(ViewLine::Points::FirstPoint, modelKnot->glRenderVec3Position());
//        m_mk1PositionChangedConnection = QObject::connect(modelKnot, &ModelKnot::positionChanged, [this](const ModelKnot * model) {
//            m_line->setPointPosition(ViewLine::Points::FirstPoint, model->glRenderVec3Position());
//        });
    }
}

void ViewSegment::setThird(const ModelKnot * modelKnot)
{
    Q_CHECK_PTR(modelKnot);
    m_mk2 = modelKnot;
    QObject::disconnect(m_mk2PositionChangedConnection);

    if (modelKnot)
    {
//        m_line->setPointPosition(ViewLine::Points::LastPoint, modelKnot->glRenderVec3Position());
//        m_mk2PositionChangedConnection = QObject::connect(modelKnot, &ModelKnot::positionChanged, [this](const ModelKnot * model) {
//            m_line->setPointPosition(ViewLine::Points::LastPoint, model->glRenderVec3Position());
//        });
    }
}

void ViewSegment::setFourth(const ModelKnot * modelKnot)
{
    Q_CHECK_PTR(modelKnot);
    m_mk3 = modelKnot;
//    QObject::disconnect(m_mk3PositionChangedConnection);

    if (modelKnot)
    {
//        m_line->setPointPosition(ViewLine::Points::LastPoint, modelKnot->glRenderVec3Position());
//        m_mk2PositionChangedConnection = QObject::connect(modelKnot, &ModelKnot::positionChanged, [this](const ModelKnot * model) {
//            m_line->setPointPosition(ViewLine::Points::LastPoint, model->glRenderVec3Position());
//        });
    }

}

void ViewSegment::draw(Camera *)
{

}

bool ViewSegment::isCentralKnot(ModelKnot * modelKnot) const
{
    return m_mk1 == modelKnot;
}

bool ViewSegment::isLeftKnot(ModelKnot * modelKnot) const
{
    return m_mk0 == modelKnot;
}

bool ViewSegment::isRigthKnot(ModelKnot * modelKnot) const
{
    return m_mk2 == modelKnot;
}

const ModelKnot * ViewSegment::mk0() const
{
    return m_mk0;
}

const ModelKnot * ViewSegment::mk1() const
{
    return m_mk1;
}

const ModelKnot * ViewSegment::mk2() const
{
    return m_mk2;
}

void ViewSegment::forgetModelKnot(ModelKnot * modelKnot)
{
    Q_CHECK_PTR(modelKnot);

    if (m_mk0 == modelKnot)
    {
        m_mk0 = nullptr;
    }
    else if (m_mk1 == modelKnot)
    {
        m_mk1 = nullptr;
    }
    else if (m_mk2 == modelKnot)
    {
        m_mk2 = nullptr;
    }
}
