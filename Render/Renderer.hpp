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
};

#endif // RENDERER_HPP
