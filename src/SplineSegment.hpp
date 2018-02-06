#pragma once

#include "glRender.h"

#include "SplineMark.hpp"

namespace glRender {

class SplineSegment : public NodeMixedWith<IDrawable>
{
public:
    SplineSegment(SplineMark * startMark, SplineMark * stopMark)
    {
        m_line = new Line(
            startMark->model()->origin(),
            stopMark->model()->origin(), 
            1.0, 
            Vec3(1.0f, 0.0f, 1.0f)
        );

        startMark->addLinePoint(m_line, Line::POINTS::FirstPoint);
         stopMark->addLinePoint(m_line, Line::POINTS::SecondPoint);

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
    Line * m_line;

};

}