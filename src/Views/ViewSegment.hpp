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
    ViewSegment(const ModelKnot *, const ModelKnot *, const ModelKnot *, const ModelKnot *);
    ~ViewSegment();

    void draw(Camera *) override;

private:
    Vec3 interpolate(float t, Vec3 p1, Vec3 p2, Vec3 r1, Vec3 r2);

private:
    QList<ViewLine *> m_lines;
    const uint m_segmentsNumber = 50;
    const Vec3 m_normalColor = {1.0f,0.0f,1.0f};
};
