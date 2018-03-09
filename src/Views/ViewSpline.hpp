#pragma once

#include "glRender.h"

#include "ViewSplineMark.hpp"
#include "ViewSplineSegment.hpp"

using namespace glRender;

class ViewSpline : public NodeMixedWith<IUpdateable>
{
public:
    ViewSpline();
    void add(ViewSplineMark * mark);
    void update() override;

private:
    std::list<ViewSplineSegment * > m_segments;
    std::list<ViewSplineMark * > m_marks;

};
