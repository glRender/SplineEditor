#pragma once

#include "glRender.h"

#include "ViewLine.hpp"

using namespace glRender;

class ModelKnot;

class ViewSplineMark : public NodeMixedWith<IDrawable, IIntersectable>
{
public:
    enum class Event
    {
        Change
    };

    ViewSplineMark(ModelKnot * model);
    ~ViewSplineMark();

    void draw(Camera * camera) override;

    const Model * model() const;

    const IBoundingBox * bb() const;

    bool intersects(const RayPtr ray) const override;

    void setOrigin(const Vec3 & origin);

    void onMouseUp(Vec3 & position, RayPtr ray, Camera * camera) override;
    void onMouseDown(Vec3 & position, RayPtr ray, Camera * camera) override;
    void onMouseMove(Vec3 & toPosition) override;

    void changeColor();

    void addLinePoint(ViewLine * line, ViewLine::POINTS point);

private:
    ModelKnot * m_model;

    std::map<ViewLine *, ViewLine::POINTS> m_points;
    AABB * m_aabb;
    Vec3 m_color;
    Model * m_mesh;
    bool m_isSelected = false;


};