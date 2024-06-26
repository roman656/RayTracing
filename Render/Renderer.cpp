#include "Renderer.hpp"

QVector3D Renderer::CastRay(const Ray& ray, const Scene& scene) noexcept
{
    const std::optional<QPair<qint32, float>> optionalIntersection = FindIntersection(ray, scene);

    if (optionalIntersection.has_value())
    {
        const auto [intersectedObjectIndex, minIntersectionDistance] = optionalIntersection.value();
        const QVector<Sphere> sceneObjects = scene.GetObjects();
        const Material resultMaterial = sceneObjects[intersectedObjectIndex].GetMaterial();
        const QVector3D intersectionPoint = ray.GetPointOnRay(minIntersectionDistance);
        const QVector3D normal = (intersectionPoint -
                sceneObjects[intersectedObjectIndex].GetCenterPoint()).normalized();

        return resultMaterial.GetDiffuseColor() * CalcDiffuseLightIntensity(intersectionPoint, normal, scene);
    }
    else
    {
        return scene.GetBackgroundColor();
    }
}


std::optional<QPair<qint32, float>> Renderer::FindIntersection(const Ray& ray, const Scene& scene) noexcept
{
    const QVector<Sphere> sceneObjects = scene.GetObjects();
    const qint32 sceneObjectsAmount = sceneObjects.size();
    const float farClipPlaneDistance = scene.GetCamera().GetFarClipPlaneDistance();

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
        return std::nullopt;
    }
    else
    {
        return QPair<qint32, float>(intersectedObjectIndex, minIntersectionDistance);
    }
}



float Renderer::CalcDiffuseLightIntensity(const QVector3D& intersectionPoint,
                                          const QVector3D& normal,
                                          const Scene& scene) noexcept
{
    const QVector<LightPoint> sceneLightPoints = scene.GetLightPoints();
    const qint32 sceneLightPointsAmount = sceneLightPoints.size();

    float diffuseLightIntensity = 0.0f;

    for (qint32 i = 0; i < sceneLightPointsAmount; ++i)
    {
        /* Направление от рассматриваемой точки на сфере к источнику света. */
        const QVector3D lightDirection = (sceneLightPoints[i].GetPosition() - intersectionPoint).normalized();

        diffuseLightIntensity += sceneLightPoints[i].GetIntensity() *
                qMax(0.0f, QVector3D::dotProduct(lightDirection, normal));
    }

    return diffuseLightIntensity;
}



float Renderer::CalcSpecularLightIntensity(const QVector3D& intersectionPoint,
                                           const QVector3D& normal,
                                           const Scene& scene) noexcept
{
    const QVector<LightPoint> sceneLightPoints = scene.GetLightPoints();
    const qint32 sceneLightPointsAmount = sceneLightPoints.size();

    float specularLightIntensity = 0.0f;

    for (qint32 i = 0; i < sceneLightPointsAmount; ++i)
    {
        /* Направление от рассматриваемой точки на сфере к источнику света. */
        const QVector3D lightDirection = (sceneLightPoints[i].GetPosition() - intersectionPoint).normalized();

        //specularLightIntensity += sceneLightPoints[i].GetIntensity() * qPow(qMax(0.0f, QVector3D::dotProduct(reflect(-lightDirection, normal)*dir)), material.GetSpecularExponent());
    }

    return specularLightIntensity;
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
