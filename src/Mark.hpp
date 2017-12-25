#ifndef MARK_H
#define MARK_H

#include "glRender.h"

namespace glRender {

class AABBNodeVisualizator;

class Mark : public NodeMixedWith<IUpdateable, IDrawable, IIntersectable>
{
public:
  Mark(Vec3 color, float size, uint i, uint j, uint k);
  ~Mark();

  void update() override;
  void draw(Camera * camera) override;
  bool intersects(const RayPtr ray) const override;

  Model * model() const;
  IBoundingBox * bb() const override;

//  void onIntersection(IIntersectable * o) override
//  {
//  }

  void onMouseUp(Vec3 & position, RayPtr ray, Camera * camera) override;
  void onMouseDown(Vec3 & position, RayPtr ray, Camera * camera) override;
  void onMouseMove(Vec3 & toPosition) override;

  void changeColor();

private:
  Model * m_model;
  AABB * m_aabb;
  AABBNodeVisualizator * m_aabbVisualizator;

  Vec3 m_color;

  uint m_i;
  uint m_j;
  uint m_k;

  bool m_isSelected = false;

};

class CameraNode : public NodeMixedWith<IUpdateable, IKeyPressable>
{
public:
    CameraNode(Camera * camera) :
        m_camera(camera)
    {
    }

    void update() override
    {
    }

    void onKeyPress(KeyboardKey key) override
    {
        switch(key)
        {
        case IKeyPressable::KeyboardKey::W: {

            m_camera->setPosition( m_camera->position() + m_camera->front() * cameraMoveSpeed );
        }; break;

        case IKeyPressable::KeyboardKey::S: {
            m_camera->setPosition( m_camera->position() - m_camera->front() * cameraMoveSpeed );
        }; break;

        case IKeyPressable::KeyboardKey::A: {
            m_camera->setPosition( m_camera->position() - m_camera->right() * cameraMoveSpeed );
        }; break;

        case IKeyPressable::KeyboardKey::D: {
            m_camera->setPosition( m_camera->position() + m_camera->right() * cameraMoveSpeed );
        }; break;

        case IKeyPressable::KeyboardKey::Q: {
            m_camera->setEulerAngles( m_camera->pitch(), m_camera->yaw() + cameraRotationSpeed, m_camera->roll() );
        }; break;

        case IKeyPressable::KeyboardKey::E: {
            m_camera->setEulerAngles( m_camera->pitch(), m_camera->yaw() - cameraRotationSpeed, m_camera->roll() );
        }; break;

        case IKeyPressable::KeyboardKey::Z: {
            m_camera->setPosition( m_camera->position() + m_camera->up() * cameraMoveSpeed );
        }; break;

        case IKeyPressable::KeyboardKey::X: {
            m_camera->setPosition( m_camera->position() - m_camera->up() * cameraMoveSpeed );
        }; break;

        case IKeyPressable::KeyboardKey::R: {
            m_camera->setEulerAngles( m_camera->pitch() + cameraRotationSpeed, m_camera->yaw(), m_camera->roll() );
        }; break;

        case IKeyPressable::KeyboardKey::F: {
            m_camera->setEulerAngles( m_camera->pitch() - cameraRotationSpeed, m_camera->yaw(), m_camera->roll() );
        }; break;

        default: {

        }

        }
    }

private:
    CameraPtr m_camera;
    float cameraMoveSpeed = 0.3f;
    float cameraRotationSpeed = 5.0f;

};


}

#endif // MARK_H
