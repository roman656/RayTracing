#include "LightPoint.hpp"

LightPoint::LightPoint(const QVector3D& position, float intensity) noexcept
{
    m_position = position;
    m_intensity = intensity;
}



QVector3D LightPoint::GetPosition() const noexcept
{
    return m_position;
}



void LightPoint::SetPosition(const QVector3D& position) noexcept
{
    m_position = position;
}



float LightPoint::GetIntensity() const noexcept
{
    return m_intensity;
}



void LightPoint::SetIntensity(float intensity) noexcept
{
    m_intensity = intensity;
}
