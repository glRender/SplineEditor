#include "CameraControl.hpp"

namespace glRender
{

CameraControl::CameraControl(Camera * camera)
    : m_camera(camera)
    , m_front(camera->front())
{
}

void CameraControl::update()
{
}

void CameraControl::onMouseUp(Vec2 normDeviceCoords, RayPtr ray, Camera *)
{
}

void CameraControl::onMouseDown(Vec2 normDeviceCoords, RayPtr ray, Camera *)
{
    lastPoint = normDeviceCoords;
}

void CameraControl::onMouseMove(Vec2 normDeviceCoords, RayPtr ray, Camera *)
{
    float xoffset = lastPoint.x - normDeviceCoords.x;
    float yoffset = lastPoint.y - normDeviceCoords.y;

    float sensitivity = 0.5f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    m_camera->setEulerAngles(pitch, yaw, m_camera->roll());
}

void CameraControl::onKeyPress(KeyboardKey key)
{
    switch (key)
    {
        case IKeyPressable::KeyboardKey::W:
        {

            m_camera->setPosition(m_camera->position() + m_camera->front() * cameraMoveSpeed);
        };
        break;

        case IKeyPressable::KeyboardKey::S:
        {
            m_camera->setPosition(m_camera->position() - m_camera->front() * cameraMoveSpeed);
        };
        break;

        case IKeyPressable::KeyboardKey::A:
        {
            m_camera->setPosition(m_camera->position() - m_camera->right() * cameraMoveSpeed);
        };
        break;

        case IKeyPressable::KeyboardKey::D:
        {
            m_camera->setPosition(m_camera->position() + m_camera->right() * cameraMoveSpeed);
        };
        break;

        case IKeyPressable::KeyboardKey::Q:
        {
            m_camera->setEulerAngles(m_camera->pitch(),
                                     m_camera->yaw() + cameraRotationSpeed,
                                     m_camera->roll());
        };
        break;

        case IKeyPressable::KeyboardKey::E:
        {
            m_camera->setEulerAngles(m_camera->pitch(),
                                     m_camera->yaw() - cameraRotationSpeed,
                                     m_camera->roll());
        };
        break;

        case IKeyPressable::KeyboardKey::Z:
        {
            m_camera->setPosition(m_camera->position() + m_camera->up() * cameraMoveSpeed);
        };
        break;

        case IKeyPressable::KeyboardKey::X:
        {
            m_camera->setPosition(m_camera->position() - m_camera->up() * cameraMoveSpeed);
        };
        break;

        case IKeyPressable::KeyboardKey::R:
        {
            m_camera->setEulerAngles(m_camera->pitch() + cameraRotationSpeed,
                                     m_camera->yaw(), m_camera->roll());
        };
        break;

        case IKeyPressable::KeyboardKey::F:
        {
            m_camera->setEulerAngles(m_camera->pitch() - cameraRotationSpeed,
                                     m_camera->yaw(), m_camera->roll());
        };
        break;

        default: {
        }
    }
}
}
