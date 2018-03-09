#pragma once

#include <QObject>

#include "ModelKnot.hpp"

class ControllerKnot : public QObject
{
public:
    ControllerKnot(ModelKnot * model, QObject * parent = nullptr)
        : m_model(model)
    {

    }

    ModelKnot * model() const
    {
        return m_model;
    }

    void mouseOnPress()
    {

    }

    void mouseOnRelesase()
    {

    }

    void mouseOnMove()
    {

    }

    const char * text = "wefwef";

private:
    ModelKnot * m_model;

};
