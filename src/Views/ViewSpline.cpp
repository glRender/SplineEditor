#include "ViewSpline.hpp"

#include <unordered_set>

#include <QObject>
#include <QDebug>

#include "ModelSpline.hpp"
#include "ModelKnot.hpp"
#include "ModelSplineEditor.hpp"

#include "ViewSegment.hpp"
#include "ViewKnot.hpp"

ViewSpline::ViewSpline(ModelSpline * modelSpline, ModelSplineEditor * modelSplineEditor)
    : m_modelSpline(modelSpline)
    , m_modelSplineEditor(modelSplineEditor)
{
    Q_CHECK_PTR(m_modelSpline);
    Q_CHECK_PTR(m_modelSplineEditor);

    auto knots = m_modelSpline->knotModels();
    for (int i=0; i < knots.size(); i++)
    {
        add(knots[i]);
    }

    QObject::connect(m_modelSpline, &ModelSpline::added, [this](ModelKnot * knot) {
        Q_CHECK_PTR(knot);
        add(knot);
    });

    QObject::connect(m_modelSpline, &ModelSpline::removed, [this](ModelKnot * knot) {
        Q_CHECK_PTR(knot);
        remove(knot);
    });
}

void ViewSpline::recreateSegments()
{
    for (auto viewSegment : m_viewSegments)
    {
        Node::remove(viewSegment.data());
        m_viewSegments.removeOne(viewSegment);
    }

    for (uint i=3; i<m_modelSpline->size(); i++)
    {
        auto firstModelKnot  = m_modelSpline->at(i-3);
        auto secondModelKnot = m_modelSpline->at(i-2);
        auto thirdModelKnot  = m_modelSpline->at(i-1);
        auto fourthModelKnot = m_modelSpline->at(i);

        auto viewSegment = QSharedPointer<ViewSegment>(
                    new ViewSegment(firstModelKnot,
                                    secondModelKnot,
                                    thirdModelKnot,
                                    fourthModelKnot), [this](ViewSegment * ViewSegment)
        {
            delete ViewSegment;
        });

        m_viewSegments.append(viewSegment);
        Node::add(viewSegment.data());
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

    QObject::connect(modelKnot, &ModelKnot::positionChanged, [this](const ModelKnot * modelKnot) {
        recreateSegments();
    });

    QObject::connect(modelKnot, &ModelKnot::paramsChanged, [this](const ModelKnot * modelKnot) {
        recreateSegments();
    });

    Node::add(viewKnot.data());
    m_viewKnotByModelKnot[modelKnot] = viewKnot;

    recreateSegments();
}

void ViewSpline::remove(ModelKnot * modelKnot)
{
    Q_CHECK_PTR(modelKnot);
    // Удалить ViewKnot
    if (m_viewKnotByModelKnot[modelKnot] != nullptr)
    {
        Node::remove(m_viewKnotByModelKnot[modelKnot].data());
        m_viewKnotByModelKnot.remove(modelKnot);
    }

    recreateSegments();
}

void ViewSpline::draw(Camera * camera)
{

}
