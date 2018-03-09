#pragma once

#include "glRender.h"

#include "ViewSplineMark.hpp"
#include "ViewSplineSegment.hpp"

class ModelSpline;

using namespace glRender;

class ViewSpline : public NodeMixedWith<IUpdateable>
{
public:
    ViewSpline()
    {

    }

    ViewSpline(ModelSpline * model);
    void add(ViewSplineMark * mark);
    void update() override;

private:
    ModelSpline * m_model;
    std::list<ViewSplineSegment * > m_segments;
    std::list<ViewSplineMark * > m_marks;

};
