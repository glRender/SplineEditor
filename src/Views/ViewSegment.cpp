#include "ViewSegment.hpp"

ViewSplineSegment::ViewSplineSegment(ViewKnot *startMark, ViewKnot *stopMark)
{
    m_line = new ViewLine(
                startMark->model()->origin(),
                stopMark->model()->origin(),
                1.0,
                Vec3(1.0f, 0.0f, 1.0f)
                );

    startMark->addLinePoint(m_line, ViewLine::POINTS::FirstPoint);
    stopMark->addLinePoint(m_line, ViewLine::POINTS::SecondPoint);

    add(startMark);
    add(stopMark);
    add(m_line);
}

void ViewSplineSegment::draw(Camera *camera)
{

}

void ViewSplineSegment::refresh()
{

}
