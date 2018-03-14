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
    }

    void setMode(EditorModeMachine::Mode mode);

private:
    ModelSplineEditor * m_model;

};
