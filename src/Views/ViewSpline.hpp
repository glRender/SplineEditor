#pragma once

#include <QMap>
#include <QSet>
#include <QSharedPointer>

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

    QMap<ModelKnot *, QSharedPointer<ViewKnot>> m_viewKnotByModelKnot;
    QMap<ModelKnot *, QSet<QSharedPointer<ViewSegment>>> m_segmentsByModelKnot;

};
