#ifndef SCENE_HPP
#define SCENE_HPP

#include <QVector>

#include "Render/Sphere.hpp"
#include "Render/Camera.hpp"

class Scene final
{
public:
    explicit Scene() noexcept;

    QVector3D GetBackgroundColor() const noexcept;
    void SetBackgroundColor(const QVector3D& backgroundColor) noexcept;

    Camera& GetCamera() noexcept;
    const Camera& GetCamera() const noexcept;
    void SetCamera(const Camera& camera) noexcept;

    void AddSphere(const Sphere& sphere) noexcept;

    QVector<Sphere>& GetObjects() noexcept;
    const QVector<Sphere>& GetObjects() const noexcept;

private:
    QVector3D m_backgroundColor;
    Camera m_camera;
    QVector<Sphere> m_objects;
};

#endif // SCENE_HPP
