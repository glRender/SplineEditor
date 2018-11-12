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

void ViewSpline::removeSegements()
{
    for (auto viewSegment : m_viewSegments)
    {
        Node::remove(viewSegment.data());
        m_viewSegments.removeOne(viewSegment);
    }
}

void ViewSpline::createSegments()
{
    // i=2 и size()+1 для создания сегментов на краях с
    // mk0==nullptr для левого крайнего сегмента и
    // mk3==nullptr для правого крайнего сегмента и
    // mk0==nullptr и mk3==nullptr для сегмента из двух узлов

    for (uint i=2; i<m_modelSpline->size()+1; i++)
    {
        auto mk0 = m_modelSpline->at(i-3);
        auto mk1 = m_modelSpline->at(i-2);
        auto mk2 = m_modelSpline->at(i-1);
        auto mk3 = m_modelSpline->at(i);

        auto viewSegment = QSharedPointer<ViewSegment>(
                    new ViewSegment(mk0, mk1, mk2, mk3), [this](ViewSegment * ViewSegment)
        {
            delete ViewSegment;
        });

        m_viewSegments.append(viewSegment);
        Node::add(viewSegment.data());
    }
}

void ViewSpline::recreateSegments()
{
    removeSegements();
    createSegments();
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
