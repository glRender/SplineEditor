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

    ViewKnot * viewKnot = new ViewKnot(modelKnot, m_modelSplineEditor);
    Node::add(viewKnot);
    m_viewKnotByModelKnot[modelKnot] = viewKnot;

    int knotIndex = m_model->knotIndex(modelKnot);

    if (knotIndex >= 1)
    {
        ModelKnot * firstKnot  = m_model->knotFromKnot(modelKnot, 2);
        ModelKnot * secondKnot = m_model->knotFromKnot(modelKnot, 1);
        ModelKnot * thirdKnot  = m_model->knotFromKnot(modelKnot, 0);

        qDebug() << firstKnot << secondKnot << thirdKnot;

        ViewSegment * segment = new ViewSegment(firstKnot, secondKnot, thirdKnot, m_modelSplineEditor);
        Node::add(segment);
        m_segmentsByModelKnot[firstKnot].push_back(segment);
        m_segmentsByModelKnot[secondKnot].push_back(segment);
        m_segmentsByModelKnot[thirdKnot].push_back(segment);
    }

}

void ViewSpline::remove(ModelKnot * modelKnot)
{
    qDebug() << "!* " << modelKnot->position();

    // Удалить ViewKnot
    if (m_viewKnotByModelKnot[modelKnot] != nullptr)
    {
        Node::remove(m_viewKnotByModelKnot[modelKnot]);
        m_viewKnotByModelKnot.erase(m_viewKnotByModelKnot.find(modelKnot));
    }

    // Удалить "центральный" ViewSegement или любой если он один
    auto & segments = m_segmentsByModelKnot[modelKnot];
    if (segments.size() == 1)
    {
        auto segment = *m_segmentsByModelKnot[modelKnot].begin();
        m_segmentsByModelKnot[modelKnot].remove(segment);
        Node::remove(segment);
        delete segment;
    }
    else if (segments.size() > 1)
    {
        qDebug() << m_segmentsByModelKnot[modelKnot].size();
        for (auto it = m_segmentsByModelKnot[modelKnot].begin(); it != m_segmentsByModelKnot[modelKnot].end(); it++)
        {
            auto segment = *it;

            segment->removeKnotPointer(modelKnot);

            qDebug() << "*******************";
            if (segment->mk0())
            {
                qDebug() << "0: " << segment->mk0()->position();
            }
            else
            {
                qDebug() << "0:  NULL";
            }

            if (segment->mk1())
            {
                qDebug() << "1: "  << segment->mk1()->position();
            }
            else
            {
                qDebug() << "1:  NULL";
            }

            if (segment->mk2())
            {
                qDebug() << "2: 3D(-0.33, 1.38, -0.9" << segment->mk2()->position();
            }
            else
            {
                qDebug() << "2:  NULL";
            }
            qDebug() << "*******************";

            if (segment->isCentralKnot(modelKnot))
            {
                m_segmentsByModelKnot[modelKnot].remove(segment);
                Node::remove(segment);
                delete segment;
                break;
            }
        }
    }

    // Подредактировать левый и правый сегменты
    qDebug() << m_segmentsByModelKnot[modelKnot].size();
    auto modelKnotNeighbors = m_model->neighbors(modelKnot);

    if (modelKnotNeighbors.first)
    {
        qDebug() << "левый сосед " << modelKnotNeighbors.first->position();
    }

    if (modelKnotNeighbors.second)
    {
        qDebug() << "правый сосед " << modelKnotNeighbors.second->position();
    }

    for (auto it = m_segmentsByModelKnot[modelKnot].begin(); it != m_segmentsByModelKnot[modelKnot].end(); it++)
    {
        auto segment = *it;

        if (segment->isRigthKnot(modelKnot))
        {
            // Это левый сегмент
            qDebug() << "Нашел левый сегмент";
            segment->setThird(modelKnotNeighbors.second);
        }
        else if (segment->isLeftKnot(modelKnot))
        {
            // Это правый сегмент
            qDebug() << "Нашел правый сегмент";
            segment->setFirst(modelKnotNeighbors.first);
        }
    }

}

void ViewSpline::draw(Camera * camera)
{

}
