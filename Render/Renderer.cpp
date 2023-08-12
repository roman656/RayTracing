#include "Renderer.hpp"

QVector3D Renderer::CastRay(const Ray& ray, const Scene& scene) noexcept
{
    const QVector<Sphere> sceneObjects = scene.GetObjects();
    const qint32 sceneObjectsAmount = sceneObjects.size();
    Material resultMaterial(scene.GetBackgroundColor());
    QVector3D normal;
    float minIntersectionDistance = -1;
    bool wasAnyIntersection = false;

    for (qint32 i = 0; i < sceneObjectsAmount; ++i)
    {
        std::optional<float> optionalDistance = sceneObjects[i].CalcIntersectionDistance(ray);

        if (optionalDistance.has_value())
        {
            float distance = optionalDistance.value();

            if (distance <= scene.GetCamera().GetDistanceToTheFarClipPlane())
            {
                if (!wasAnyIntersection || distance < minIntersectionDistance)
                {
                    wasAnyIntersection = true;
                    minIntersectionDistance = distance;
                    resultMaterial.SetDiffuseColor(sceneObjects[i].GetMaterial().GetDiffuseColor());
                    normal = (ray.GetPointOnRay(distance) - sceneObjects[i].GetCenterPoint()).normalized();
                }
            }
        }
    }

    return resultMaterial.GetDiffuseColor();
}



void Renderer::Render(const Scene& scene, FrameBuffer& frameBuffer) noexcept
{
    const qint32 width = frameBuffer.GetWidth();
    const qint32 height = frameBuffer.GetHeight();
    const float indentToPixelCenter = 0.5f;    // Половина пикселя.
    const Camera& camera = scene.GetCamera();
    float screenWidth = 2.0f * qTan(camera.GetFieldOfViewAngle() * 0.5f) * camera.GetScreenCameraDistance();
    float screenHalfWidth = screenWidth * 0.5f;
    float screenAspectRatio = static_cast<float>(width) / static_cast<float>(height);
    QVector<QVector3D>& frameBufferData = frameBuffer.GetData();

    for (qint32 rowIndex = 0; rowIndex < height; ++rowIndex)
    {
        for (qint32 columnIndex = 0; columnIndex < width; ++columnIndex)
        {
            float frameBufferPixelX = static_cast<float>(columnIndex);
            float frameBufferPixelY = static_cast<float>(rowIndex);    // Растёт в направлении, противоположном мировой оси OY.

            /* Эти координаты задаются в мировых единицах. Screen - плоскость в 3D-пространстве. */
            float screenPixelX =  ((frameBufferPixelX + indentToPixelCenter) / static_cast<float>(width) * screenWidth - screenHalfWidth) * screenAspectRatio;
            float screenPixelY = -((frameBufferPixelY + indentToPixelCenter) / static_cast<float>(height) * screenWidth - screenHalfWidth);

            Ray ray(camera.GetPosition(),
                    QVector3D(screenPixelX, screenPixelY, -camera.GetScreenCameraDistance() + camera.GetPosition().z()));

            frameBufferData[columnIndex + rowIndex * width] = CastRay(ray, scene);
        }
    }
}
