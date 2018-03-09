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
        m_controllerSpline = new ControllerSpline(m_model->modelSpline());
    }

    ControllerSpline * controllerSpline() const
    {
        return m_controllerSpline;
    }

private:
    ModelSplineEditor * m_model;
    ControllerSpline * m_controllerSpline;

};
