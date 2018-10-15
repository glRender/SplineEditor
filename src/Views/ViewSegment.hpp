#pragma once

#include "glRender.h"
#include <functional>

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

    QList<Vec3> approximate(float t, Vec3 p1, Vec3 p2, std::function<Vec3(float t)>);

private:
    QList<ViewLine *> m_lines;
    const uint m_curvatureAngle = 10;
    const Vec3 m_normalColor = {1.0f,0.0f,1.0f};
};
