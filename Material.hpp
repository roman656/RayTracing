#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <QVector3D>

class Material final
{
public:
    explicit Material() noexcept;
    explicit Material(const QVector3D& diffuseColor) noexcept;

    QVector3D GetDiffuseColor() const noexcept;
    void SetDiffuseColor(const QVector3D& diffuseColor) noexcept;

private:
    QVector3D m_diffuseColor;
};

#endif // MATERIAL_HPP
