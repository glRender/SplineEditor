#pragma once

#include "glRender.h"

#include "SplineMarkView.hpp"
#include "SplineSegmentView.hpp"

namespace glRender {

class SplineView : public NodeMixedWith<IUpdateable>
{
public:
    SplineView()
    {

    }

    void add(SplineMarkView * mark)
    {
        // Node::add(mark);
        if (m_marks.size() > 0)
        {
            SplineMarkView * lastMark = m_marks.back();
            SplineSegmentView * segment = new SplineSegmentView(lastMark, mark);
            auto updateSegment = [segment]() {
                segment->refresh();
            };
            lastMark->addCallbackOn(SplineMarkView::Event::Change, updateSegment);
            mark->addCallbackOn(SplineMarkView::Event::Change, updateSegment);
            Node::add(segment);

            m_segments.push_back(segment);
        }

        m_marks.push_back(mark);

    }

    void update() override
    {

    }

private:
    std::list<SplineSegmentView * > m_segments;
    std::list<SplineMarkView * > m_marks;

};

}
