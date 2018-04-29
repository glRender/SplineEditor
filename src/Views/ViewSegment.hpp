#pragma once

#include "glRender.h"

#include <QObject>

#include "ViewKnot.hpp"

class ViewLine;
class ModelKnot;

using namespace glRender;

class ViewSegment : public NodeMixedWith<IDrawable>
{
public:
    ViewSegment(ModelKnot *, ModelKnot *, ModelKnot *, ModelSplineEditor *);
    ~ViewSegment();

    void draw(Camera *) override;

private:
    ViewLine * m_line;

    ModelKnot * m_mk0 = nullptr;
    ModelKnot * m_mk1 = nullptr;
    ModelKnot * m_mk2 = nullptr;

    QMetaObject::Connection m_mk0PositionChangedConnection;
    QMetaObject::Connection m_mk2PositionChangedConnection;

};
