#pragma once

#include "glRender.h"

#include "ViewLine.hpp"

using namespace glRender;

class ModelKnot;
class ViewSegment;
class ModelSplineEditor;

class ViewKnot : public NodeMixedWith<IDrawable, IIntersectable>
{
public:
    enum class Event
    {
        Change
    };

    ViewKnot(ModelKnot * controller, ModelSplineEditor * modelSplineEditor);
    ~ViewKnot();

    void draw(Camera * camera) override;
    bool intersects(const RayPtr ray) const override;
    void onMouseUp(Vec3 & position, RayPtr ray, Camera * camera) override;
    void onMouseDown(Vec3 & position, RayPtr ray, Camera * camera) override;
    void onMouseMove(Vec3 & toPosition) override;

    const Model * mesh() const;
    ModelKnot * model() const;

    const IBoundingBox * bb() const;
    void setPosition(const Vec3 &);
    void changeColor();
    void notifyLineAsFirstPoint(ViewSegment * segment);
    void notifyLineAsLastPoint(ViewSegment * segment);
    ViewSegment * segmentFirstKnotOf() const;
    ViewSegment *  segmentLastKnotOf() const;

private:
    ModelKnot * m_model;
    ModelSplineEditor * m_modelSplineEditor;

    ViewSegment * m_firstKnotOfSegment = nullptr;
    ViewSegment * m_lastKnotOfSegment = nullptr;

    AABB * m_aabb;
    Vec3 m_color;
    Model * m_mesh;
    bool m_isSelected = false;


};
