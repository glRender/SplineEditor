#pragma once

#include "glRender.h"

#include "ViewSplineMark.hpp"

namespace glRender {

class ViewSplineSegment : public NodeMixedWith<IDrawable>
{
public:
    ViewSplineSegment(ViewSplineMark * startMark, ViewSplineMark * stopMark)
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

    void draw(Camera * camera) override
    {

    }

    void refresh()
    {

    }

private:
    ViewLine * m_line;

};

}
