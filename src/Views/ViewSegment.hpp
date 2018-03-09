#pragma once

#include "glRender.h"

#include "ViewKnot.hpp"

using namespace glRender;

class ViewSplineSegment : public NodeMixedWith<IDrawable>
{
public:
    ViewSplineSegment(ViewKnot * startMark, ViewKnot * stopMark);
    void draw(Camera * camera) override;
    void refresh();

private:
    ViewLine * m_line;

};
