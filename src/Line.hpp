#pragma once

#include "glRender.h"

#include "geometryBuffer.hpp"

namespace glRender {

class Line : public NodeMixedWith<IUpdateable, IDrawable>
{
public:
  enum class POINTS
  {
    FirstPoint,
    SecondPoint,
  };

  Line(Vec3 p0, Vec3 p1, uint segmentsNumber, Vec3 color);
  ~Line();

  void update() override;
  void draw(Camera * camera) override;

  void setPointPosition(POINTS point, Vec3 & position)
  {
    std::cout << position << std::endl;
    // Buffer<Vec3> * buffer = (Buffer<Vec3>) m_model->geometry()->get("vertex");
    AbstractBuffer * b = m_model->geometry()->get("vertex");
    Buffer<Vec3> * buffer = dynamic_cast<Buffer<Vec3> *>(b);
    if (point == POINTS::FirstPoint)
    {
      buffer->rewrite(0, position);
    }
    else
    {
      buffer->rewrite(1, position);      
    }
  }

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

}
