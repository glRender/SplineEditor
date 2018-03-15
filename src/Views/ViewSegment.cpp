#include "ViewSegment.hpp"

ViewSegment::ViewSegment(ViewKnot *startViewKnot, ViewKnot *stopViewKnot)
{
    m_line = new ViewLine(
                startViewKnot->mesh()->origin(),
                stopViewKnot->mesh()->origin(),
                1.0,
                Vec3(1.0f, 0.0f, 1.0f)
                );

    startViewKnot->notifyLineAsFirstPoint(m_line);
     stopViewKnot->notifyLineAsLastPoint(m_line);
    add(m_line);
}

void ViewSegment::draw(Camera *camera)
{

}
