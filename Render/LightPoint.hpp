#ifndef LIGHTPOINT_HPP
#define LIGHTPOINT_HPP

#include <QVector3D>

class LightPoint final
{
public:
    explicit LightPoint(const QVector3D& position = QVector3D(), float intensity = 1.0f) noexcept;

    QVector3D GetPosition() const noexcept;
    void SetPosition(const QVector3D& position) noexcept;

    float GetIntensity() const noexcept;
    void SetIntensity(float intensity) noexcept;

private:
    QVector3D m_position;
    float m_intensity;
};

#endif // LIGHTPOINT_HPP
