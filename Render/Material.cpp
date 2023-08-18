#include "Material.hpp"

Material::Material(const QVector3D& ambientColor,
                   const QVector3D& diffuseColor,
                   const QVector3D& specularColor,
                   float shininess) noexcept
{
    m_ambientColor = ambientColor;
    m_diffuseColor = diffuseColor;
    m_specularColor = specularColor;
    m_shininess = shininess;
}



QVector3D Material::GetAmbientColor() const noexcept
{
    return m_ambientColor;
}



void Material::SetAmbientColor(const QVector3D& ambientColor) noexcept
{
    m_ambientColor = ambientColor;
}



QVector3D Material::GetDiffuseColor() const noexcept
{
    return m_diffuseColor;
}



void Material::SetDiffuseColor(const QVector3D& diffuseColor) noexcept
{
    m_diffuseColor = diffuseColor;
}



QVector3D Material::GetSpecularColor() const noexcept
{
    return m_specularColor;
}



void Material::SetSpecularColor(const QVector3D& specularColor) noexcept
{
    m_specularColor = specularColor;
}



float Material::GetShininess() const noexcept
{
    return m_shininess;
}



void Material::SetShininess(float shininess) noexcept
{
    m_shininess = shininess;
}
