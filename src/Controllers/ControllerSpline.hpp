#pragma once

#include <QObject>
#include <QSharedPointer>
#include <QMap>

#include "ModelKnot.hpp"
#include "ModelSpline.hpp"
#include "ControllerKnot.hpp"

class ControllerSpline : public QObject
{
    Q_OBJECT
public:
    ControllerSpline(ModelSpline * model, QObject * parent = nullptr)
        : m_model(model)
    {
        connect(m_model.data(), &ModelSpline::added, this, [this](ModelKnot * knot) {
            addController(knot);
        });

        QList<ModelKnot*> knotModels = m_model->knotModels();
        for (auto knotModel : knotModels)
        {
            addController(knotModel);
        }
    }

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
    QSharedPointer<ModelSpline> m_model;
    QMap<ModelKnot *, ControllerKnot *> m_controllerKnotByModelKnot;
    QList<ControllerKnot * > m_controllersKnots;

};
