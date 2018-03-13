#pragma once

#include <QObject>
#include <QSharedPointer>
#include <QMap>

#include "ModelKnot.hpp"
#include "ModelSpline.hpp"
#include "ModelSplineEditor.hpp"

#include "ControllerKnot.hpp"

class ControllerSpline : public QObject
{
    Q_OBJECT
public:
    ControllerSpline(ModelSpline * modelSpline, ModelSplineEditor * modelEditor, QObject * parent = nullptr)
        : m_modelSpline(modelSpline)
        , m_modelEditor(modelEditor)
    {
        connect(m_modelSpline, &ModelSpline::added, this, [this](ModelKnot * knot) {
            addController(knot);
        });

        QList<ModelKnot*> knotModels = m_modelSpline->knotModels();
        for (auto knotModel : knotModels)
        {
            addController(knotModel);
        }
    }

//    ModelSpline * model() const
//    {
//        return m_model;
//    }

    ControllerKnot * knotController(ModelKnot * knot) const
    {
        return m_controllerKnotByModelKnot[knot];
    }

    QList<ControllerKnot * > knotsControllers()
    {
        return m_controllersKnots;
    }

    void addController(ModelKnot * knot)
    {
        ControllerKnot * controllerKnot = new ControllerKnot(knot);
        m_controllerKnotByModelKnot[knot] = controllerKnot;
        m_controllersKnots.append(controllerKnot);
        emit added(controllerKnot);
    }

    void removeController(QSharedPointer<ModelKnot> knot)
    {

    }

signals:
    void added(ControllerKnot *);

private:
    QList<QSharedPointer<ModelKnot>> m_knots;

private:
    ModelSpline * m_modelSpline;
    ModelSplineEditor * m_modelEditor;
    QMap<ModelKnot *, ControllerKnot *> m_controllerKnotByModelKnot;
    QList<ControllerKnot * > m_controllersKnots;

};
