#include "Material.hpp"

Material::Material(const QVector2D& albedo,
                   const QVector3D& diffuseColor,
                   float specularExponent) noexcept
{
    m_albedo = albedo;
    m_specularExponent = specularExponent;
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



QVector2D Material::GetAlbedo() const noexcept
{
    return m_albedo;
}



void Material::SetAlbedo(const QVector2D& albedo) noexcept
{
    m_albedo = albedo;
}



float Material::GetSpecularExponent() const noexcept
{
    return m_specularExponent;
}



void Material::SetSpecularExponent(float specularExponent) noexcept
{
    m_specularExponent = specularExponent;
}
