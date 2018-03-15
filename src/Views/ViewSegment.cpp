#include "ViewSegment.hpp"

ViewSegment::ViewSegment(ViewKnot * firsViewKnot, ViewKnot * lastViewKnot)
    : m_firsViewKnot(firsViewKnot)
    , m_lastViewKnot(lastViewKnot)
{
    m_line = new ViewLine(
                firsViewKnot->mesh()->origin(),
                lastViewKnot->mesh()->origin(),
                1.0,
                Vec3(1.0f, 0.0f, 1.0f)
                );

    firsViewKnot->notifyLineAsFirstPoint(this);
    lastViewKnot->notifyLineAsLastPoint (this);
    add(m_line);
}

void ViewSegment::draw(Camera *camera)
{

}

void ViewSegment::setPointPosition(ViewLine::Points point, Vec3 &position)
{
    m_line->setPointPosition(point, position);
}

ViewKnot *ViewSegment::firstKnot() const
{
    return m_firsViewKnot;
}

ViewKnot *ViewSegment::lastKnot() const
{
    return m_lastViewKnot;
}
