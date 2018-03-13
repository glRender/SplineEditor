#pragma once

#include <QObject>
#include <QSharedPointer>
#include <QMap>

#include "ModelSplineEditor.hpp"
#include "ControllerSpline.hpp"

class ControllerSplineEditor : public QObject
{
    Q_OBJECT
public:
    ControllerSplineEditor(ModelSplineEditor * model, QObject * parent = nullptr)
        : m_model(model)
    {
//        m_controllerSpline = new ControllerSpline(m_model->modelSpline(), m_model);

//        connect(m_controllerSpline, &ControllerSpline::added, this, [this](ControllerKnot * controllerKnot) {
//            connect(controllerKnot, &ControllerKnot::onMouseDown, this, [=]() {
//                if (m_model->mode() == EditorModeMachine::Mode::Deletion)
//                {
//                    m_controllerSpline->model()->remove(controllerKnot->model());
//                }
//                else
//                {

//                }

//            });

//            connect(controllerKnot, &ControllerKnot::onMouseUp, this, [=]() {

//            });

//            connect(controllerKnot, &ControllerKnot::onMouseMove, this, [=]() {

//            });

//        });
    }

//    ControllerSpline * controllerSpline() const
//    {
//        return m_controllerSpline;
//    }

private:
    ModelSplineEditor * m_model;
//    ControllerSpline * m_controllerSpline;

};
