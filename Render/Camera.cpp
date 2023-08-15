#include "Camera.hpp"

Camera::Camera(const QVector3D& position) noexcept
{
    m_position = position;
}



QVector3D Camera::GetPosition() const noexcept
{
    return m_position;
}



void Camera::SetPosition(const QVector3D& position) noexcept
{
    m_position = position;
}



float Camera::GetFieldOfViewAngle() const noexcept
{
    return m_fieldOfViewAngle;
}



void Camera::SetFieldOfViewAngle(float fieldOfViewAngle) noexcept
{
    m_fieldOfViewAngle = fieldOfViewAngle;
}



float Camera::GetNearClipPlaneDistance() const noexcept
{
    return m_nearClipPlaneDistance;
}



void Camera::SetNearClipPlaneDistance(float nearClipPlaneDistance) noexcept
{
    m_nearClipPlaneDistance = nearClipPlaneDistance;
}



float Camera::GetFarClipPlaneDistance() const noexcept
{
    return m_farClipPlaneDistance;
}



void Camera::SetFarClipPlaneDistance(float farClipPlaneDistance) noexcept
{
    m_farClipPlaneDistance = farClipPlaneDistance;
}
