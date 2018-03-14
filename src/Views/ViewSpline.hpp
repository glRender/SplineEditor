#pragma once

#include <QMap>

#include "glRender.h"

#include "ViewKnot.hpp"
#include "ViewSegment.hpp"

class ModelSpline;

using namespace glRender;

class ViewSpline : public NodeMixedWith<IUpdateable>
{
public:
    ViewSpline()
    {

    }

    ViewSpline(ModelSpline * model);
    void add(ViewKnot * mark);
    void remove(ViewKnot * mark);

    ViewKnot * byModelKnot(ModelKnot *);
    void update() override;

private:
    ModelSpline * m_model;
    std::list<ViewSplineSegment * > m_segments;
    std::list<ViewKnot * > m_marks;
    QMap<ModelKnot *, ViewKnot *> m_viewByModel;

};
