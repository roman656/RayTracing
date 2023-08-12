#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <QVector3D>
#include <QtMath>

class Camera
{
public:
    explicit Camera(const QVector3D& position = QVector3D()) noexcept;

    QVector3D GetPosition() const noexcept;
    void SetPosition(const QVector3D& position) noexcept;

    float GetFieldOfViewAngle() const noexcept;
    void SetFieldOfViewAngle(float fieldOfViewAngle) noexcept;

    float GetScreenCameraDistance() const noexcept;
    void SetScreenCameraDistance(float screenCameraDistance) noexcept;

    float GetDistanceToTheFarClipPlane() const noexcept;
    void SetDistanceToTheFarClipPlane(float distanceToTheFarClipPlane) noexcept;

private:
    QVector3D m_position;
    float m_screenCameraDistance = 1.0f;    // distanceToTheNearClipPlane
    float m_distanceToTheFarClipPlane = 1000.0f;
    float m_fieldOfViewAngle = qDegreesToRadians(90.0f);
};

#endif // CAMERA_HPP
