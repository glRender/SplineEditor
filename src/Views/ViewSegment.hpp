#pragma once

#include "glRender.h"

#include "ViewKnot.hpp"
#include "ViewLine.hpp"

using namespace glRender;

class ViewSegment : public NodeMixedWith<IDrawable>
{
public:
//    ViewSegment(ViewKnot *, ViewKnot *);
    ViewSegment(ModelKnot *, ModelKnot *, ModelKnot *, ModelSplineEditor *);

    void draw(Camera * camera) override;
    void setPointPosition(ViewLine::Points point, const Vec3 & position);

//    ViewKnot * firstKnot() const;
//    ViewKnot *  lastKnot() const;

private:
    ViewLine * m_line;

    ModelKnot * m_mk0 = nullptr;
    ModelKnot * m_mk1 = nullptr;
    ModelKnot * m_mk2 = nullptr;
};
