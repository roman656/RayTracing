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



float Camera::GetScreenCameraDistance() const noexcept
{
    return m_screenCameraDistance;
}



void Camera::SetScreenCameraDistance(float screenCameraDistance) noexcept
{
    m_screenCameraDistance = screenCameraDistance;
}



float Camera::GetDistanceToTheFarClipPlane() const noexcept
{
    return m_distanceToTheFarClipPlane;
}



void Camera::SetDistanceToTheFarClipPlane(float distanceToTheFarClipPlane) noexcept
{
    m_distanceToTheFarClipPlane = distanceToTheFarClipPlane;
}
