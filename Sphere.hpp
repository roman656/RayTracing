#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <QVariant>

#include "Ray.hpp"

class Sphere final
{
public:
    explicit Sphere(float radius, const QVector3D& centerPoint, const QVector3D& color) noexcept;

    QVariant WasIntersected(const Ray& ray) const noexcept;

    float GetRadius() const noexcept;
    void SetRadius(float radius) noexcept;

    QVector3D GetCenterPoint() const noexcept;
    void SetCenterPoint(const QVector3D& centerPoint) noexcept;

    QVector3D GetColor() const noexcept;
    void SetColor(const QVector3D& color) noexcept;

private:
    QVector3D m_color;
    QVector3D m_centerPoint;
    float m_radius;
};

#endif // SPHERE_HPP
