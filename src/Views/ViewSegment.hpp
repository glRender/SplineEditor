#pragma once

#include "glRender.h"
#include <functional>

#include <QObject>

#include "ViewKnot.hpp"

class ViewLine;
class ModelKnot;
class ModelSpline;

using namespace glRender;

class ViewSegment : public NodeMixedWith<IDrawable>
{
public:
    ViewSegment(const ModelSpline *, const ModelKnot *, const ModelKnot *, const ModelKnot *, const ModelKnot *);
    ~ViewSegment();

    void draw(Camera *) override;

private:
    QList<ViewLine *> m_lines;
    const uint m_curvatureAngle = 3;
    const Vec3 m_normalColor = {1.0f,0.0f,1.0f};
};
