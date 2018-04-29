#pragma once

#include "glRender.h"

using namespace glRender;

class ViewLine : public NodeMixedWith<IDrawable>
{
public:
  enum class Points
  {
    FirstPoint,
    LastPoint,
  };

  ViewLine(Vec3 p0, Vec3 p1, uint segmentsNumber, Vec3 color);
  ~ViewLine();

  void draw(Camera *) override;
  void setPointPosition(Points point, const Vec3 & position);

  Model * model();
  IBoundingBox * bb() const;

private:
  Model * m_model = nullptr;
  AABB * m_aabb = nullptr;

  Vec3 m_p0;
  Vec3 m_p1;

  int m_segmentsNumber;

  float m_r;
  float m_g;
  float m_b;
  Vec3 m_color;
  float m_speed;

};
