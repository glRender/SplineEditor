#include "ViewSpline.hpp"
#include "ModelSpline.hpp"

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
    ViewKnot * firstViewKnot = viewKnot->segmentLastKnotOf()->firstKnot();
    ViewKnot *  lastViewKnot = viewKnot->segmentFirstKnotOf()->lastKnot();

//    ViewKnot * firstViewKnot = byModelKnot(m_model->knotModels()[0]);
//    ViewKnot *  lastViewKnot = byModelKnot(m_model->knotModels()[1]);

//    firstViewKnot->changeColor();
//    lastViewKnot->changeColor();

    Node::remove(viewKnot->segmentLastKnotOf());
    Node::remove(viewKnot->segmentFirstKnotOf());
    Node::remove(viewKnot);
    m_viewKnots.remove(viewKnot);

    ViewSegment * segment = new ViewSegment(firstViewKnot, lastViewKnot);
    m_segments.push_back(segment);
    Node::add(segment);
}

ViewKnot *ViewSpline::byModelKnot(ModelKnot * modelKnot)
{
    return m_viewByModel[modelKnot];
}

void ViewSpline::update()
{

}
