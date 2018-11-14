#include "CameraControl.hpp"

namespace glRender {

CameraControl::CameraControl(Camera * camera)
    : m_camera(camera)
    , m_front(camera->front())
{
}

void CameraControl::onKeyPress(KeyboardKey key)
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

}


