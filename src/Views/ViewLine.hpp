#pragma once

#include "glRender.h"

#include "geometryBuffer.hpp"

using namespace glRender;

class ViewLine : public NodeMixedWith<IUpdateable, IDrawable>
{
public:
  enum class Points
  {
    FirstPoint,
    LastPoint,
  };

  ViewLine(Vec3 p0, Vec3 p1, uint segmentsNumber, Vec3 color);
  ~ViewLine();

  void update() override;
  void draw(Camera * camera) override;

  void setPointPosition(Points point, Vec3 & position);

  Model * model()/* override*/;
  IBoundingBox * bb() const/* override*/;

private:
  Model * m_model;
  AABB * m_aabb;

  Vec3 m_p0;
  Vec3 m_p1;

  int m_segmentsNumber;

  float m_r;
  float m_g;
  float m_b;
  Vec3 m_color;
  float m_speed;

};
