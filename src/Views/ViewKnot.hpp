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

    ViewKnot(ModelKnot *, ModelSplineEditor *);
    ViewKnot(Vec3 position);
    void construct();

    ~ViewKnot();

    void draw(Camera *) override;
    bool intersects(const RayPtr ray) const override;
    void onMouseUp(Vec3 & position, RayPtr ray, Camera *) override;
    void onMouseDown(Vec3 & position, RayPtr ray, Camera *) override;
    void onMouseMove(Vec3 & toPosition) override;

    const Model * mesh() const;
    ModelKnot * model() const;

    const IBoundingBox * bb() const;
    void setPosition(const Vec3 &);

    void setSelected(bool selected);

    void setDragging(bool dragging);
    bool isDragging() const;

    void changeColor(const Vec3 & color);
    void notifyLineAsFirstPoint(ViewSegment * segment);
    void notifyLineAsLastPoint(ViewSegment * segment);
    ViewSegment * segmentFirstKnotOf() const;
    ViewSegment *  segmentLastKnotOf() const;

private:
    ModelKnot * m_model = nullptr;
    ModelSplineEditor * m_modelSplineEditor = nullptr;

    ViewSegment * m_firstKnotOfSegment = nullptr;
    ViewSegment * m_lastKnotOfSegment = nullptr;

    AABB * m_aabb = nullptr;
    Vec3 m_currentColor;
    Model * m_mesh = nullptr;

    const Vec3 m_selectionColor = Vec3(1,0,0);

    bool m_isDragging = false;
    const Vec3 m_draggingColor = Vec3(0,0,1);
    const Vec3 m_normalColor = Vec3(0,1,0);

};
