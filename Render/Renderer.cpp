#include "Renderer.hpp"

QVector3D Renderer::CastRay(const Ray& ray, const Scene& scene) noexcept
{
    const QVector<Sphere> sceneObjects = scene.GetObjects();
    const QVector<LightPoint> sceneLightPoints = scene.GetLightPoints();
    const qint32 sceneObjectsAmount = sceneObjects.size();
    const qint32 sceneLightPointsAmount = sceneLightPoints.size();
    const float farClipPlaneDistance = scene.GetCamera().GetFarClipPlaneDistance();

    Material resultMaterial(scene.GetBackgroundColor());
    float minIntersectionDistance = -1;
    qint32 intersectedObjectIndex = -1;
    bool wasAnyIntersection = false;

    for (qint32 i = 0; i < sceneObjectsAmount; ++i)
    {
        const std::optional<float> optionalDistance = sceneObjects[i].CalcIntersectionDistance(ray);

        if (optionalDistance.has_value())
        {
            const float distance = optionalDistance.value();

            if (distance <= farClipPlaneDistance)
            {
                if (!wasAnyIntersection || distance < minIntersectionDistance)
                {
                    wasAnyIntersection = true;
                    minIntersectionDistance = distance;
                    intersectedObjectIndex = i;
                }
            }
        }
    }

    if (!wasAnyIntersection)
    {
        return resultMaterial.GetDiffuseColor();
    }
    else
    {
        const QVector3D intersectionPoint = ray.GetPointOnRay(minIntersectionDistance);
        const QVector3D normal = (intersectionPoint -
                sceneObjects[intersectedObjectIndex].GetCenterPoint()).normalized();

        float diffuseLightIntensity = 0.0f;

        resultMaterial = sceneObjects[intersectedObjectIndex].GetMaterial();

        for (qint32 j = 0; j < sceneLightPointsAmount; ++j)
        {
            /* Направление от рассматриваемой точки на сфере к источнику света. */
            const QVector3D lightDirection = (sceneLightPoints[j].GetPosition() -
                    intersectionPoint).normalized();

            diffuseLightIntensity += sceneLightPoints[j].GetIntensity() *
                    qMax(0.0f, QVector3D::dotProduct(lightDirection, normal));
        }

        return resultMaterial.GetDiffuseColor() * diffuseLightIntensity;
    }
}



void Renderer::Render(const Scene& scene, FrameBuffer& frameBuffer) noexcept
{
    const qint32 width = frameBuffer.GetWidth();
    const qint32 height = frameBuffer.GetHeight();
    const Camera& camera = scene.GetCamera();
    const float indentToPixelCenter = 0.5f;    // Половина пикселя.
    const float screenWidth = 2.0f * qTan(camera.GetFieldOfViewAngle() * 0.5f) * camera.GetNearClipPlaneDistance();
    const float screenHalfWidth = screenWidth * 0.5f;
    const float screenAspectRatio = static_cast<float>(width) / static_cast<float>(height);

    for (qint32 rowIndex = 0; rowIndex < height; ++rowIndex)
    {
        for (qint32 columnIndex = 0; columnIndex < width; ++columnIndex)
        {
            const float frameBufferPixelX = static_cast<float>(columnIndex);
            const float frameBufferPixelY = static_cast<float>(rowIndex);    // Растёт в направлении, противоположном мировой оси OY.

            /* Эти координаты задаются в мировых единицах. Screen - плоскость в 3D-пространстве. */
            const float screenPixelX =  ((frameBufferPixelX + indentToPixelCenter) / static_cast<float>(width) * screenWidth - screenHalfWidth) * screenAspectRatio;
            const float screenPixelY = -((frameBufferPixelY + indentToPixelCenter) / static_cast<float>(height) * screenWidth - screenHalfWidth);

            const QVector3D pointOnScreen(screenPixelX,
                                          screenPixelY,
                                          -camera.GetNearClipPlaneDistance() + camera.GetPosition().z());
            const Ray ray(camera.GetPosition(), pointOnScreen);

            frameBuffer.SetPixel(rowIndex, columnIndex, CastRay(ray, scene));
        }
    }
}
