#pragma once

#include "glRender.h"

namespace glRender {

class CameraControl : public NodeMixedWith<IKeyPressable>
{
public:
    CameraControl(Camera *);
    void onKeyPress(KeyboardKey key) override;

private:
    CameraPtr m_camera;
    float cameraMoveSpeed = 0.1f;
    float cameraRotationSpeed = 1.0f;

};

}
