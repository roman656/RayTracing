#include "Scene.hpp"

Scene::Scene() noexcept
{

}



QVector3D Scene::GetBackgroundColor() const noexcept
{
    return m_backgroundColor;
}



void Scene::SetBackgroundColor(const QVector3D& backgroundColor) noexcept
{
    m_backgroundColor = backgroundColor;
}



void Scene::AddSphere(const Sphere& sphere) noexcept
{
    m_objects.append(sphere);
}



void Scene::SetCamera(const Camera& camera) noexcept
{
    m_camera = camera;
}



Camera& Scene::GetCamera() noexcept
{
    return m_camera;
}



const Camera& Scene::GetCamera() const noexcept
{
    return m_camera;
}



QVector<Sphere>& Scene::GetObjects() noexcept
{
    return m_objects;
}



const QVector<Sphere>& Scene::GetObjects() const noexcept
{
    return m_objects;
}
