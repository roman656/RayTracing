#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "Render/Scene.hpp"
#include "Render/FrameBuffer.hpp"

class Renderer final
{
public:
    static void Render(const Scene& scene, FrameBuffer& frameBuffer) noexcept;

private:
    static QVector3D CastRay(const Ray& ray, const Scene& scene) noexcept;
    static std::optional<QPair<qint32, float>> FindIntersection(const Ray& ray, const Scene& scene) noexcept;
    static float CalcDiffuseLightIntensity(const QVector3D& intersectionPoint,
                                           const QVector3D& normal,
                                           const Scene& scene) noexcept;
    static float CalcSpecularLightIntensity(const QVector3D& intersectionPoint,
                                            const QVector3D& normal,
                                            const Scene& scene) noexcept;
};

#endif // RENDERER_HPP
