#include "ViewSpline.hpp"



ViewSpline::ViewSpline(ModelSpline * model)
    : m_model(model)
{

}

void ViewSpline::add(ViewKnot * viewKnot)
{
    m_viewByModel[viewKnot->model()] = viewKnot;

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
    m_viewKnots.remove(viewKnot);
}

ViewKnot *ViewSpline::byModelKnot(ModelKnot * modelKnot)
{
    return m_viewByModel[modelKnot];
}

void ViewSpline::update()
{

}
