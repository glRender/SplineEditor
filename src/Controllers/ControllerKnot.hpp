#pragma once

#include <QObject>

#include "ModelKnot.hpp"

class ControllerKnot : public QObject
{
    Q_OBJECT
public:
    ControllerKnot(ModelKnot * model, QObject * parent = nullptr)
        : m_model(model)
    {

    }

    ModelKnot * model() const
    {
        return m_model;
    }

    void mouseUp()
    {
        emit onMouseUp();
    }

    void mouseDown()
    {
        emit onMouseDown();
    }

    void mouseMove()
    {
        emit onMouseMove();
    }

signals:
    void added(ControllerKnot *);
    void onMouseUp();
    void onMouseDown();
    void onMouseMove();

private:
    ModelKnot * m_model;

};
