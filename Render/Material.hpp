#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <QVector3D>
#include <QVector2D>

class Material final
{
public:
    explicit Material(const QVector2D& albedo = QVector2D(1, 0),
                      const QVector3D& diffuseColor = QVector3D(),
                      float specularExponent = 0.0f) noexcept;

    QVector3D GetDiffuseColor() const noexcept;
    void SetDiffuseColor(const QVector3D& diffuseColor) noexcept;

    QVector2D GetAlbedo() const noexcept;
    void SetAlbedo(const QVector2D& albedo) noexcept;

    float GetSpecularExponent() const noexcept;
    void SetSpecularExponent(float specularExponent) noexcept;

private:
    float m_specularExponent;
    QVector2D m_albedo;
    QVector3D m_diffuseColor;
};

#endif // MATERIAL_HPP
