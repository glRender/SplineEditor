#pragma once

#include "glRender.h"

#include "ViewLine.hpp"

using namespace glRender;

class ModelKnot;
class ViewSegment;

class ViewKnot : public NodeMixedWith<IDrawable, IIntersectable>
{
public:
    enum class Event
    {
        Change
    };

    ViewKnot(ModelKnot * controller, std::function<void()> onMouseUp = [](){});
    ~ViewKnot();

    void draw(Camera * camera) override;

    const Model * mesh() const;
    ModelKnot * model() const;

    const IBoundingBox * bb() const;

    bool intersects(const RayPtr ray) const override;

    void setOrigin(const Vec3 & origin);

    void onMouseUp(Vec3 & position, RayPtr ray, Camera * camera) override;
    void onMouseDown(Vec3 & position, RayPtr ray, Camera * camera) override;
    void onMouseMove(Vec3 & toPosition) override;

    void setOnMouseUpCallback(std::function<void()>);

    void changeColor();

    void notifyLineAsFirstPoint(ViewSegment * segment);
    void notifyLineAsLastPoint(ViewSegment * segment);

    ViewSegment * segmentFirstKnotOf() const;
    ViewSegment *  segmentLastKnotOf() const;


private:
    ModelKnot * m_model;

    std::function<void ()> m_onMouseUpCallback;

//    std::map<ViewSegment *, ViewLine::Points> m_pointOfSegment;
    ViewSegment * m_firstKnotOfSegment = nullptr;
    ViewSegment * m_lastKnotOfSegment = nullptr;

    AABB * m_aabb;
    Vec3 m_color;
    Model * m_mesh;
    bool m_isSelected = false;


};
