#include "Material.hpp"

Material::Material(const QVector3D& diffuseColor) noexcept
{
    m_diffuseColor = diffuseColor;
}



QVector3D Material::GetDiffuseColor() const noexcept
{
    return m_diffuseColor;
}



void Material::SetDiffuseColor(const QVector3D& diffuseColor) noexcept
{
    m_diffuseColor = diffuseColor;
}
