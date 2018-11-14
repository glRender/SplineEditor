#pragma once

#include "glRender.h"

namespace glRender {

class CameraControl : public NodeMixedWith<IUpdateable, IKeyPressable, IMouseListenable>
{
public:
    CameraControl(Camera *);

    void update() override
    {
    }

    void onMouseUp(Vec2 normDeviceCoords, RayPtr ray, Camera *) override
    {

    }

    void onMouseDown(Vec2 normDeviceCoords, RayPtr ray, Camera *) override
    {
        lastPoint = normDeviceCoords;
    }

    void onMouseMove(Vec2 normDeviceCoords, RayPtr ray, Camera *) override
    {
//        std::cout << "ray dir" << ray->dir().toStdString();
//        std::cout << m_front << std::endl;
//        m_front = ray->dir();
//        std::cout << m_front << std::endl;
        float xoffset = normDeviceCoords.x - lastPoint.x;
        float yoffset = normDeviceCoords.y - lastPoint.y;

        float sensitivity = 0.5f;
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        yaw += xoffset;
//        yaw = abs((uint)yaw % 360);

        pitch += yoffset;

        if(pitch > 89.0f)
            pitch = 89.0f;
        if(pitch < -89.0f)
            pitch = -89.0f;

//        Vec3 front;
//        front.x = cos(MATH_DEG_TO_RAD(yaw)) * cos(MATH_DEG_TO_RAD(pitch));
//        front.y = sin(MATH_DEG_TO_RAD(pitch));
//        front.z = sin(MATH_DEG_TO_RAD(yaw)) * cos(MATH_DEG_TO_RAD(pitch));
//        m_front = front.normalize();

//        m_camera->setPosition( m_front );
        m_camera->setEulerAngles(pitch, yaw, m_camera->roll() );

    }

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
