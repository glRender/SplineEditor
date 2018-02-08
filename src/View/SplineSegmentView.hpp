#pragma once

#include "glRender.h"

#include "SplineMarkView.hpp"

namespace glRender {

class SplineSegmentView : public NodeMixedWith<IDrawable>
{
public:
    SplineSegmentView(SplineMarkView * startMark, SplineMarkView * stopMark)
    {
        m_line = new LineView(
            startMark->model()->origin(),
            stopMark->model()->origin(), 
            1.0, 
            Vec3(1.0f, 0.0f, 1.0f)
        );

        startMark->addLinePoint(m_line, LineView::POINTS::FirstPoint);
         stopMark->addLinePoint(m_line, LineView::POINTS::SecondPoint);

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
    LineView * m_line;

};

}
