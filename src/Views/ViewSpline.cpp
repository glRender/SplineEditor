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
    Q_CHECK_PTR(m_model);
    Q_CHECK_PTR(m_modelSplineEditor);

    auto knots = m_model->knotModels();
    for (int i=0; i < knots.size(); i++)
    {
        add(knots[i]);
    }
}

void ViewSpline::add(ModelKnot * modelKnot)
{
    Q_CHECK_PTR(modelKnot);

    auto viewKnot = QSharedPointer<ViewKnot>(new ViewKnot(modelKnot), [this](ViewKnot * viewKnot)
    {
        delete viewKnot;
    });

    viewKnot->subscribeOnMouseUp([this, viewKnot, modelKnot]() -> void {
         if (m_modelSplineEditor->mode()  == ModelSplineEditor::Mode::Moving)
         {
             viewKnot->setDragging(false);
         }
         else if (m_modelSplineEditor->mode() == ModelSplineEditor::Mode::Removing)
         {
             m_modelSplineEditor->modelSpline()->remove(modelKnot);
         }
    });

    viewKnot->subscribeOnMouseDown([this, viewKnot, modelKnot]() -> void {
        if (m_modelSplineEditor->mode() == ModelSplineEditor::Mode::Moving)
        {
            modelKnot->setSelected(true);
            viewKnot->setDragging(true);
        }
        else if (m_modelSplineEditor->mode() == ModelSplineEditor::Mode::Selection)
        {
            modelKnot->setSelected(true);
        }
    });

    viewKnot->subscribeOnMouseMove([this, modelKnot](Vec3 & position) -> void {
        if (m_modelSplineEditor->mode() == ModelSplineEditor::Mode::Moving)
        {
            modelKnot->setPosition({position.x, position.y, position.z});
        }
    });

    Node::add(viewKnot.data());
    m_viewKnotByModelKnot[modelKnot] = viewKnot;

    int knotIndex = m_model->knotIndex(modelKnot);

    if (knotIndex >= 1)
    {
        ModelKnot * firstKnot  = m_model->knotFromKnot(modelKnot, 2);
        ModelKnot * secondKnot = m_model->knotFromKnot(modelKnot, 1);
        ModelKnot * thirdKnot  = m_model->knotFromKnot(modelKnot, 0);

        auto viewSegment = QSharedPointer<ViewSegment>(new ViewSegment(firstKnot, secondKnot, thirdKnot), [this](ViewSegment * viewSegment)
        {
            delete viewSegment;
        });

        Node::add(viewSegment.data());

        if (firstKnot)
        {
            m_segmentsByModelKnot[firstKnot].insert(viewSegment);
        }

        if (secondKnot)
        {
            m_segmentsByModelKnot[secondKnot].insert(viewSegment);
        }

        if (thirdKnot)
        {
            m_segmentsByModelKnot[thirdKnot].insert(viewSegment);
        }
    }

}

void ViewSpline::remove(ModelKnot * modelKnot)
{
    Q_CHECK_PTR(modelKnot);
    // Подредактировать левый и правый сегменты
    auto modelKnotNeighbors = m_model->neighbors(modelKnot);
    for (auto viewSegment : m_segmentsByModelKnot[modelKnot])
    {
        if (viewSegment->isRigthKnot(modelKnot))
        {
            // Это левый сегмент
            viewSegment->setThird(modelKnotNeighbors.second);
        }
        else if (viewSegment->isLeftKnot(modelKnot))
        {
            // Это правый сегмент
            viewSegment->setFirst(modelKnotNeighbors.first);
        }
    }

    // Удалить "центральный" ViewSegement или любой если он один
    auto & segments = m_segmentsByModelKnot[modelKnot];
    if (segments.size() == 1)
    {
        auto viewSegment = *m_segmentsByModelKnot[modelKnot].begin();
        m_segmentsByModelKnot[modelKnot].remove(viewSegment);
        if (!viewSegment.isNull())
        {
            Node::remove(viewSegment.data());
        }
    }
    else if (segments.size() > 1)
    {
        for (auto viewSegment : m_segmentsByModelKnot[modelKnot])
        {
            if (viewSegment->isCentralKnot(modelKnot))
            {
                m_segmentsByModelKnot[modelKnot].remove(viewSegment);
                if (!viewSegment.isNull())
                {
                    Node::remove(viewSegment.data());
                }
                break;
            }
            viewSegment->forgetModelKnot(modelKnot);
        }
    }

    // Удалить ViewKnot
    if (m_viewKnotByModelKnot[modelKnot] != nullptr)
    {
        if (!m_viewKnotByModelKnot[modelKnot].isNull())
        {
            Node::remove(m_viewKnotByModelKnot[modelKnot].data());
        }
        m_viewKnotByModelKnot.remove(modelKnot);
    }
}

void ViewSpline::draw(Camera * camera)
{

}
