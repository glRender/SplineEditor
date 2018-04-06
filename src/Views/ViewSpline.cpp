#include "ViewSpline.hpp"
#include "ModelSpline.hpp"

ViewSpline::ViewSpline(ModelSpline * model)
    : m_model(model)
{

}

void ViewSpline::add(ViewKnot * viewKnot)
{
    assert(viewKnot);

    if (viewKnot->model() != nullptr)
    {
        m_viewByModel[viewKnot->model()] = viewKnot;
    }

    Node::add(viewKnot);
    if (m_viewKnots.size() > 0)
    {
        ViewKnot * lastViewKnot = m_viewKnots.back();
        ViewSegment * segment = new ViewSegment(lastViewKnot, viewKnot);
        m_segments.push_back(segment);
        Node::add(segment);
    }
    m_viewKnots.push_back(viewKnot);
}

void ViewSpline::remove(ViewKnot * viewKnot)
{
    ViewSegment * leftSegment = viewKnot->segmentLastKnotOf();
    ViewSegment * rightSegment = viewKnot->segmentFirstKnotOf();

    if (leftSegment != nullptr)
    {
        Node::remove(leftSegment);
    }

    if (rightSegment != nullptr)
    {
        Node::remove(rightSegment);
    }

    Node::remove(viewKnot);
    m_viewKnots.remove(viewKnot);

    if (leftSegment != nullptr and rightSegment != nullptr)
    {
        ViewSegment * segment = new ViewSegment(leftSegment->firstKnot(), rightSegment->lastKnot());
        m_segments.push_back(segment);
        Node::add(segment);
    }

}

ViewKnot * ViewSpline::byModelKnot(ModelKnot * modelKnot)
{
    return m_viewByModel[modelKnot];
}

void ViewSpline::update()
{

}
