#pragma once

#include <QMap>
#include <QSet>
#include <QSharedPointer>

#include "glRender.h"

class ModelSpline;
class ModelKnot;
class ModelSplineEditor;

class ViewSegment;
class ViewKnot;

using namespace glRender;

class ViewSpline : public NodeMixedWith<IDrawable>
{
public:
    ViewSpline(ModelSpline *, ModelSplineEditor *);
    void add(ModelKnot *);
    void remove(ModelKnot *);

    void draw(Camera *) override;

private:
    void recreateSegments();
    void removeSegements();
    void createSegments();

private:
    ModelSpline * m_modelSpline = nullptr;
    ModelSplineEditor * m_modelSplineEditor = nullptr;

    QMap<ModelKnot *, QSharedPointer<ViewKnot>> m_viewKnotByModelKnot;
    QList<QSharedPointer<ViewSegment>>          m_viewSegments;
    const Vec3 m_normalColor = Vec3(1.0f,0.0f,1.0f);
};
