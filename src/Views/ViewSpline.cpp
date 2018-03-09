#include "ViewSpline.hpp"



ViewSpline::ViewSpline(ModelSpline * model)
    : m_model(model)
{

}

void ViewSpline::add(ViewKnot *mark)
{
    // Node::add(mark);
    if (m_marks.size() > 0)
    {
        ViewKnot * lastMark = m_marks.back();
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

void ViewSpline::update()
{

}
