#pragma once

#include <QMap>
#include <unordered_set>

#include "glRender.h"

class ModelSpline;
class ModelKnot;
class ViewSegment;
class ViewKnot;
class ModelSplineEditor;

using namespace glRender;

class ViewSpline : public NodeMixedWith<IDrawable>
{
public:
    ViewSpline(ModelSpline *, ModelSplineEditor *);
    void add(ModelKnot *);

    void draw(Camera *) override;

private:
    ModelSpline * m_model = nullptr;
    ModelSplineEditor * m_modelSplineEditor = nullptr;
    std::list<ViewKnot * > m_viewKnots;

    QMap<ModelKnot *, std::unordered_set<ViewSegment *>> m_segmentsByModelKnot;

};
