#include "ViewSpline.hpp"

#include <unordered_set>

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
        ViewKnot * vk = new ViewKnot(knots[i], m_modelSplineEditor);
        Node::add(vk);
        m_viewKnots.push_back(vk);
    }

    if (knots.size() == 2)
    {
        ViewSegment * segment = new ViewSegment(knots[0], nullptr, knots[1], m_modelSplineEditor);
        Node::add(segment);
        auto segments = m_segmentsByModelKnot[knots[0]];
        segments.insert(segment);
        segments = m_segmentsByModelKnot[knots[0]];
        segments.insert(segment);
    }
    else if (knots.size() >= 3)
    {
        for (int i=0; i < knots.size(); i++)
        {
            if (i + 2 < knots.size())
            {
//                ModelKnot * mk0 = knots[i+0];
//                ModelKnot * mk1 = knots[i+1];
//                ModelKnot * mk2 = knots[i+2];

                ViewSegment * segment = new ViewSegment(knots[i+0], knots[i+1], knots[i+2], m_modelSplineEditor);
                auto segments = m_segmentsByModelKnot[knots[i+0]];
                segments.insert(segment);
                segments = m_segmentsByModelKnot[knots[i+1]];
                segments.insert(segment);
                segments = m_segmentsByModelKnot[knots[i+2]];
                segments.insert(segment);
                Node::add(segment);
            }
            else
            {
//                ModelKnot * mk0 = knots[i+0];
//                ModelKnot * mk1 = knots[i+1];

                ViewSegment * segment = new ViewSegment(knots[i+0], nullptr, knots[i+1], m_modelSplineEditor);
                auto segments = m_segmentsByModelKnot[knots[i+0]];
                segments.insert(segment);
                segments = m_segmentsByModelKnot[knots[i+1]];
                segments.insert(segment);
                Node::add(segment);
                break;
            }
        }
    }

}

void ViewSpline::add(ModelKnot * modelKnot)
{
    assert(modelKnot);
    assert(m_modelSplineEditor);

    ViewKnot * vk = new ViewKnot(modelKnot, m_modelSplineEditor);
    Node::add(vk);
    m_viewKnots.push_back(vk);

    if (m_viewKnots.size() == 2)
    {
        ModelKnot * mk0 = nullptr;
        ModelKnot * mk1 = nullptr;
        auto neighbors = m_model->neighbors(modelKnot);
        if (neighbors.first)
        {
            mk0 = neighbors.first;
            mk1 = modelKnot;
        }
        else if (neighbors.second)
        {
            mk0 = modelKnot;
            mk1 = neighbors.second;
        }

        ViewSegment * segment = new ViewSegment(mk0, nullptr, mk1, m_modelSplineEditor);
        Node::add(segment);
        auto segments = m_segmentsByModelKnot[modelKnot];
        segments.insert(segment);
    }
    else if (m_viewKnots.size() >= 3)
    {
        auto getSegments = [this](ModelKnot * modelKnot) -> std::unordered_set<ViewSegment *> {
            auto neighbors = m_model->neighbors(modelKnot);
            auto currentModelKnotSegments = m_segmentsByModelKnot[modelKnot];
            std::unordered_set<ViewSegment *> leftNeighborSegments = {};
            std::unordered_set<ViewSegment *> rightNeighborSegments = {};
            if (neighbors.first)
            {
                leftNeighborSegments     = m_segmentsByModelKnot[neighbors.first];
            }
            if (neighbors.second)
            {
                rightNeighborSegments    = m_segmentsByModelKnot[neighbors.second];
            }
            std::unordered_set<ViewSegment *> segments = {};
            segments.insert(    leftNeighborSegments.begin(), leftNeighborSegments.end());
            segments.insert(currentModelKnotSegments.begin(), currentModelKnotSegments.end());
            segments.insert(   rightNeighborSegments.begin(),    rightNeighborSegments.end());
            return segments;
        };

        auto segments = getSegments(modelKnot);
        for (auto segment : segments)
        {
            Node::remove(segment);
            delete segment;
        }

        auto neighbors = m_model->neighbors(modelKnot);
        if (neighbors.first and neighbors.second)
        {
            ViewSegment * segment = new ViewSegment(neighbors.first, modelKnot, neighbors.second, m_modelSplineEditor);
            Node::add(segment);
            auto segments = m_segmentsByModelKnot[modelKnot];
            segments.insert(segment);

        }
    }
}

void ViewSpline::draw(Camera * camera)
{

}
