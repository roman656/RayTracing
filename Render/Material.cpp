#include "Material.hpp"

Material::Material(const QVector3D& diffuseColor) noexcept
{
    m_diffuseColor = diffuseColor;
}



Material::Material() noexcept : Material(QVector3D())
{}



QVector3D Material::GetDiffuseColor() const noexcept
{
    return m_diffuseColor;
}



void Material::SetDiffuseColor(const QVector3D& diffuseColor) noexcept
{
    m_diffuseColor = diffuseColor;
}
