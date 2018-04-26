#pragma once

#include <QMap>
#include <unordered_set>

#include "glRender.h"

#include "ViewKnot.hpp"
#include "ViewSegment.hpp"

class ModelSpline;
class ModelKnot;
class ViewSegment;
class ModelSplineEditor;

using namespace glRender;

class ViewSpline : public NodeMixedWith<IDrawable>
{
public:
//    ViewSpline(ModelSpline *);
    ViewSpline(ModelSpline *, ModelSplineEditor *);

//    ViewSpline();

//    void add(ViewKnot *);
//    void remove(ViewKnot *);

    void add(ModelKnot *);

//    ViewKnot * byModelKnot(ModelKnot *);
    void draw(Camera *) override;

private:
    ModelSpline * m_model = nullptr;
    ModelSplineEditor * m_modelSplineEditor = nullptr;
//    std::list<ViewSegment * > m_segments;
    std::list<ViewKnot * > m_viewKnots;
//    QMap<ModelKnot *, ViewKnot *> m_viewByModel;

    QMap<ModelKnot *, std::unordered_set<ViewSegment *>> m_segmentsByModelKnot;

};
