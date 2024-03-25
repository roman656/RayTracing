#include "Sphere.hpp"

#include <QtMath>

Sphere::Sphere(float radius, const QVector3D& centerPoint, const Material& material) noexcept
{
    m_radius = radius;
    m_centerPoint = centerPoint;
    m_material = material;
}



QVector3D Sphere::Reflect(const QVector3D& I, const QVector3D& normal) const noexcept
{
    return I - 2.0f * I * normal * normal;
}



std::optional<float> Sphere::CalcIntersectionDistance(const Ray& ray) const noexcept
{
    const QVector3D rayDirection = ray.GetDirection();
    const QVector3D fromOriginToCenter = m_centerPoint - ray.GetOriginPoint();

    const float a = QVector3D::dotProduct(rayDirection, rayDirection);
    const float b = 2.0f * QVector3D::dotProduct(fromOriginToCenter, rayDirection);
    const float c = QVector3D::dotProduct(fromOriginToCenter, fromOriginToCenter) - m_radius * m_radius;
    const float discriminant = b * b - 4 * a * c;

    if (discriminant > 0.0f)
    {
        const float x1 = qAbs((-b + static_cast<float>(qSqrt(discriminant))) / (2.0f * a));
        const float x2 = qAbs((-b - static_cast<float>(qSqrt(discriminant))) / (2.0f * a));

        return qMin(x1, x2);
    }
    else if (discriminant == 0.0f)
    {
        return qAbs(-b / (2.0f * a));
    }
    else
    {
        return std::nullopt;
    }
}



float Sphere::GetRadius() const noexcept
{
    return m_radius;
}



void Sphere::SetRadius(float radius) noexcept
{
    m_radius = radius;
}



QVector3D Sphere::GetCenterPoint() const noexcept
{
    return m_centerPoint;
}



void Sphere::SetCenterPoint(const QVector3D& centerPoint) noexcept
{
    m_centerPoint = centerPoint;
}



Material Sphere::GetMaterial() const noexcept
{
    return m_material;
}



void Sphere::SetMaterial(const Material& material) noexcept
{
    m_material = material;
}
