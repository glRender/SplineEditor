#pragma once

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
    void update() override;

private:
    ModelSpline * m_model;
    std::list<ViewSplineSegment * > m_segments;
    std::list<ViewKnot * > m_marks;

};
