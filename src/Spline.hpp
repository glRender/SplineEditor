#pragma once

#include "glRender.h"

#include "SplineMark.hpp"
#include "SplineSegment.hpp"

namespace glRender {

class Spline : public NodeMixedWith<IUpdateable>
{
public:
    Spline()
    {

    }

    void add(SplineMark * mark)
    {
        // Node::add(mark);
        if (m_marks.size() > 0)
        {
            SplineMark * lastMark = m_marks.back();
            SplineSegment * segment = new SplineSegment(lastMark, mark);
            auto updateSegment = [segment]() {
                segment->refresh();
            };
            lastMark->addCallbackOn(SplineMark::Event::Change, updateSegment);
            mark->addCallbackOn(SplineMark::Event::Change, updateSegment);
            Node::add(segment);

            m_segments.push_back(segment);
        }

        m_marks.push_back(mark);

    }

    void update() override
    {

    }

private:
    std::list<SplineSegment * > m_segments;
    std::list<SplineMark * > m_marks;

};

}