#include "Ray.hpp"

Ray::Ray(const QVector3D& originPoint, const QVector3D& pointOnRay) noexcept
{
    m_direction = (pointOnRay - originPoint).normalized();
    m_originPoint = originPoint;
}



QVector3D Ray::GetOriginPoint() const noexcept
{
    return m_originPoint;
}



void Ray::SetOriginPoint(const QVector3D& originPoint) noexcept
{
    m_originPoint = originPoint;
}



QVector3D Ray::GetDirection() const noexcept
{
    return m_direction;
}



void Ray::SetDirection(const QVector3D& pointOnRay) noexcept
{
    m_direction = (pointOnRay - m_originPoint).normalized();
}



QVector3D Ray::GetPointOnRay(float parameter) const noexcept
{
    return m_originPoint + parameter * m_direction;
}
