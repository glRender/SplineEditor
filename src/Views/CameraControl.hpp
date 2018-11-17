#pragma once

#include "glRender.h"

namespace glRender {

class CameraControl : public NodeMixedWith<IUpdateable, IKeyPressable, IMouseListenable>
{
public:
    CameraControl(Camera *);

    void update() override;
    void onMouseUp(Vec2 normDeviceCoords, RayPtr ray, Camera *) override;
    void onMouseDown(Vec2 normDeviceCoords, RayPtr ray, Camera *) override;
    void onMouseMove(Vec2 normDeviceCoords, RayPtr ray, Camera *) override;
    void onKeyPress(KeyboardKey key) override;

private:
    CameraPtr m_camera;
    Vec3 m_front;
    Vec2 lastPoint;
    float yaw = 0;
    float pitch = 0;

    float cameraMoveSpeed = 0.1f;
    float cameraRotationSpeed = 1.0f;

};

}
