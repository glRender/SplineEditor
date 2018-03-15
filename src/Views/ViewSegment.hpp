#pragma once

#include "glRender.h"

#include "ViewKnot.hpp"

using namespace glRender;

class ViewSegment : public NodeMixedWith<IDrawable>
{
public:
    ViewSegment(ViewKnot * startMark, ViewKnot * stopMark);
    void draw(Camera * camera) override;

private:
    ViewLine * m_line;

};
