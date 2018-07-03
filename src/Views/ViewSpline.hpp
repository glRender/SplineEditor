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
    void remove(ModelKnot *);

    void draw(Camera *) override;

private:
    ModelSpline * m_model = nullptr;
    ModelSplineEditor * m_modelSplineEditor = nullptr;

    std::map<ModelKnot *, ViewKnot * > m_viewKnotByModelKnot;
    QMap<ModelKnot *, std::list<ViewSegment *>> m_segmentsByModelKnot;

};
