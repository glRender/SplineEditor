#pragma once

#include "glRender.h"

#include "ViewSplineMark.hpp"

using namespace glRender;

class ViewSplineSegment : public NodeMixedWith<IDrawable>
{
public:
    ViewSplineSegment(ViewSplineMark * startMark, ViewSplineMark * stopMark);
    void draw(Camera * camera) override;
    void refresh();

private:
    ViewLine * m_line;

};
