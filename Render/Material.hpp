#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <QVector3D>

class Material final
{
public:
    explicit Material(const QVector3D& ambientColor = QVector3D(),
                      const QVector3D& diffuseColor = QVector3D(),
                      const QVector3D& specularColor = QVector3D(),
                      float shininess = 0.0f) noexcept;

    QVector3D GetAmbientColor() const noexcept;
    void SetAmbientColor(const QVector3D& ambientColor) noexcept;

    QVector3D GetDiffuseColor() const noexcept;
    void SetDiffuseColor(const QVector3D& diffuseColor) noexcept;

    QVector3D GetSpecularColor() const noexcept;
    void SetSpecularColor(const QVector3D& specularColor) noexcept;

    float GetShininess() const noexcept;
    void SetShininess(float shininess) noexcept;

private:
    QVector3D m_ambientColor;
    QVector3D m_diffuseColor;
    QVector3D m_specularColor;
    float m_shininess;
};

#endif // MATERIAL_HPP
