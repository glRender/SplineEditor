#include "ViewSegment.hpp"

#include "ModelKnot.hpp"

//ViewSegment::ViewSegment(ViewKnot * firstViewKnot, ViewKnot * lastViewKnot)
//    : m_firsViewKnot(firstViewKnot)
//    , m_lastViewKnot(lastViewKnot)
//{
//    m_line = new ViewLine(
//                firstViewKnot->mesh()->origin(),
//                lastViewKnot->mesh()->origin(),
//                1.0,
//                Vec3(1.0f, 0.0f, 1.0f)
//                );

//    firstViewKnot->notifyLineAsFirstPoint(this);
//    lastViewKnot->notifyLineAsLastPoint (this);

//    add(m_line);
//}

ViewSegment::ViewSegment(ModelKnot * mk0, ModelKnot * mk1, ModelKnot * mk2, ModelSplineEditor * modelSplineEditor)
    : m_mk0(mk0)
    , m_mk1(mk1)
    , m_mk2(mk2)
{
    m_line = new ViewLine(mk0->glRenderVec3Position(),
                          mk2->glRenderVec3Position(),
                          1.0,
                          Vec3(1.0f, 0.0f, 1.0f));

//    firstViewKnot->notifyLineAsFirstPoint(this);
//    lastViewKnot->notifyLineAsLastPoint (this);

    add(m_line);
}

void ViewSegment::draw(Camera *camera)
{

}

void ViewSegment::setPointPosition(ViewLine::Points point, const Vec3 & position)
{
    m_line->setPointPosition(point, position);
}

//ViewKnot *ViewSegment::firstKnot() const
//{
//    return m_firsViewKnot;
//}

//ViewKnot *ViewSegment::lastKnot() const
//{
//    return m_lastViewKnot;
//}
