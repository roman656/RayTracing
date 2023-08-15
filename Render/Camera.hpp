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

    float GetNearClipPlaneDistance() const noexcept;
    void SetNearClipPlaneDistance(float nearClipPlaneDistance) noexcept;

    float GetFarClipPlaneDistance() const noexcept;
    void SetFarClipPlaneDistance(float farClipPlaneDistance) noexcept;

private:
    QVector3D m_position;
    float m_nearClipPlaneDistance = 1.0f;
    float m_farClipPlaneDistance = 1000.0f;
    float m_fieldOfViewAngle = qDegreesToRadians(90.0f);
};

#endif // CAMERA_HPP
