#ifndef RAY_HPP
#define RAY_HPP

#include <QVector3D>

class Ray final
{
public:
    explicit Ray(const QVector3D& originPoint, const QVector3D& pointOnRay) noexcept;

    QVector3D GetOriginPoint() const noexcept;
    void SetOriginPoint(const QVector3D& originPoint) noexcept;

    QVector3D GetDirection() const noexcept;
    void SetDirection(const QVector3D& pointOnRay) noexcept;

    QVector3D GetPointOnRay(float parameter) const noexcept;

private:
    QVector3D m_originPoint;
    QVector3D m_direction;
};

#endif // RAY_HPP
