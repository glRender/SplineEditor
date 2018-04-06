#include "ViewSegment.hpp"

ViewSegment::ViewSegment(ViewKnot * firstViewKnot, ViewKnot * lastViewKnot)
    : m_firsViewKnot(firstViewKnot)
    , m_lastViewKnot(lastViewKnot)
{
    m_line = new ViewLine(
                firstViewKnot->mesh()->origin(),
                lastViewKnot->mesh()->origin(),
                1.0,
                Vec3(1.0f, 0.0f, 1.0f)
                );

    firstViewKnot->notifyLineAsFirstPoint(this);
    lastViewKnot->notifyLineAsLastPoint (this);

    add(m_line);
}

void ViewSegment::draw(Camera *camera)
{

}

void ViewSegment::setPointPosition(ViewLine::Points point, const Vec3 & position)
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
