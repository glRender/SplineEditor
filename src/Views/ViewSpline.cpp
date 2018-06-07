#include "ViewSpline.hpp"

#include <unordered_set>

#include <QDebug>

#include "ModelSpline.hpp"
#include "ModelKnot.hpp"
#include "ModelSplineEditor.hpp"

#include "ViewSegment.hpp"
#include "ViewKnot.hpp"
#include "ViewSegment.hpp"

ViewSpline::ViewSpline(ModelSpline * model, ModelSplineEditor * modelSplineEditor)
    : m_model(model)
    , m_modelSplineEditor(modelSplineEditor)
{
    assert(m_model);
    assert(m_modelSplineEditor);

    auto knots = m_model->knotModels();
    for (int i=0; i < knots.size(); i++)
    {
        add(knots[i]);
    }
}

void ViewSpline::add(ModelKnot * modelKnot)
{
    assert(modelKnot);
    assert(m_modelSplineEditor);

    ViewKnot * vk = new ViewKnot(modelKnot, m_modelSplineEditor);
    Node::add(vk);

    int knotIndex = m_model->knotIndex(modelKnot);

    ModelKnot * firstKnot  = nullptr;
    ModelKnot * secondKnot = nullptr;
    ModelKnot * thirdKnot  = nullptr;

    if (knotIndex != -1)
    {
        firstKnot  = m_model->knotFromKnot(modelKnot, 2);
        secondKnot = m_model->knotFromKnot(modelKnot, 1);
        thirdKnot  = m_model->knotFromKnot(modelKnot, 0);
    }

    if (knotIndex == 1)
    {
        ViewSegment * segment = new ViewSegment(firstKnot, secondKnot, thirdKnot, m_modelSplineEditor);
        Node::add(segment);
    }

    if (knotIndex >= 2)
    {
        ViewSegment * segment = new ViewSegment(firstKnot, secondKnot, thirdKnot, m_modelSplineEditor);
        Node::add(segment);
    }

}

void ViewSpline::draw(Camera * camera)
{

}
