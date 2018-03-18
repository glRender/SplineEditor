#pragma once

#include "glRender.h"

#include "ViewKnot.hpp"
#include "ViewLine.hpp"

using namespace glRender;

class ViewSegment : public NodeMixedWith<IDrawable>
{
public:
    ViewSegment(ViewKnot * firstViewKnot, ViewKnot * lastViewKnot);
    void draw(Camera * camera) override;
    void setPointPosition(ViewLine::Points point, const Vec3 & position);

    ViewKnot * firstKnot() const;
    ViewKnot *  lastKnot() const;

private:
    ViewLine * m_line;
    ViewKnot * m_firsViewKnot = nullptr;
    ViewKnot * m_lastViewKnot = nullptr;
};
