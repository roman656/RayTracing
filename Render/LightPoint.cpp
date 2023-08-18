#include "LightPoint.hpp"

LightPoint::LightPoint(const QVector3D& position, const QVector3D& color, float intensity) noexcept
{
    m_position = position;
    m_color = color;
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



QVector3D LightPoint::GetColor() const noexcept
{
    return m_color;
}



void LightPoint::SetColor(const QVector3D& color) noexcept
{
    m_color = color;
}



float LightPoint::GetIntensity() const noexcept
{
    return m_intensity;
}



void LightPoint::SetIntensity(float intensity) noexcept
{
    m_intensity = intensity;
}
