#pragma once

#include "glRender.h"

#include "ViewSplineMark.hpp"
#include "ViewSplineSegment.hpp"

namespace glRender {

class ViewSpline : public NodeMixedWith<IUpdateable>
{
public:
    ViewSpline()
    {

    }

    void add(ViewSplineMark * mark)
    {
        // Node::add(mark);
        if (m_marks.size() > 0)
        {
            ViewSplineMark * lastMark = m_marks.back();
            ViewSplineSegment * segment = new ViewSplineSegment(lastMark, mark);
//            auto updateSegment = [segment]() {
//                segment->refresh();
//            };
//            lastMark->addCallbackOn(SplineMarkView::Event::Change, updateSegment);
//            mark->addCallbackOn(SplineMarkView::Event::Change, updateSegment);
            Node::add(segment);

            m_segments.push_back(segment);
        }

        m_marks.push_back(mark);

    }

    void update() override
    {

    }

private:
    std::list<ViewSplineSegment * > m_segments;
    std::list<ViewSplineMark * > m_marks;

};

}
