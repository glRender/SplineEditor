#pragma once

#include "glRender.h"

namespace glRender {

class CameraControl : public NodeMixedWith<IUpdateable, IKeyPressable>
{
public:
    CameraControl(Camera * camera);
    void update() override;
    void onKeyPress(KeyboardKey key) override;

private:
    CameraPtr m_camera;
    float cameraMoveSpeed = 0.3f;
    float cameraRotationSpeed = 5.0f;

};


}
