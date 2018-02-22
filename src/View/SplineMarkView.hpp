#pragma once

#include "glRender.h"

#include "LineView.hpp"

using namespace glRender;

class KnotModel;

class SplineMarkView : public NodeMixedWith<IDrawable, IIntersectable>
{
public:
    enum class Event
    {
        Change
    };

    SplineMarkView(KnotModel * model);
    ~SplineMarkView();

    void draw(Camera * camera) override;

    const Model * model() const;

    const IBoundingBox * bb() const;

    bool intersects(const RayPtr ray) const override;

    void setOrigin(const Vec3 & origin);

    void onMouseUp(Vec3 & position, RayPtr ray, Camera * camera) override;
    void onMouseDown(Vec3 & position, RayPtr ray, Camera * camera) override;
    void onMouseMove(Vec3 & toPosition) override;

    void changeColor();

    void addLinePoint(LineView * line, LineView::POINTS point);

private:
    KnotModel * m_model;

    std::map<LineView *, LineView::POINTS> m_points;
    AABB * m_aabb;
    Vec3 m_color;
    Model * m_mesh;
    bool m_isSelected = false;


};
