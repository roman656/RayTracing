#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <optional>

#include "Ray.hpp"
#include "Material.hpp"

class Sphere final
{
public:
    explicit Sphere(float radius, const QVector3D& centerPoint, const Material& material) noexcept;

    std::optional<float> CalcIntersectionDistance(const Ray& ray) const noexcept;

    float GetRadius() const noexcept;
    void SetRadius(float radius) noexcept;

    QVector3D GetCenterPoint() const noexcept;
    void SetCenterPoint(const QVector3D& centerPoint) noexcept;

    Material GetMaterial() const noexcept;
    void SetMaterial(const Material& material) noexcept;

private:
    Material m_material;
    QVector3D m_centerPoint;
    float m_radius;
};

#endif // SPHERE_HPP
