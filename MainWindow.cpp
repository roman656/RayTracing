#include "MainWindow.hpp"

#include <QApplication>
#include <QDesktopWidget>
#include <QVBoxLayout>
#include <QDate>
#include <QStringBuilder>
#include <QDir>

#include "Config.hpp"

MainWindow::MainWindow(QWidget* parent) noexcept : QMainWindow(parent)
{
    m_startButton = new QPushButton(QStringLiteral(" Старт"), this);
    m_startButton->setIcon(QIcon(QStringLiteral(":/start_icon.png")));
    m_startButton->setIconSize(QSize(ICON_SIZE, ICON_SIZE));
    m_startButton->setStyleSheet(QStringLiteral("background-color: green;"));

    m_saveButton = new QPushButton(QStringLiteral(" Сохранить"), this);
    m_saveButton->setIcon(QIcon(QStringLiteral(":/save_icon.png")));
    m_saveButton->setIconSize(QSize(ICON_SIZE, ICON_SIZE));
    m_saveButton->setStyleSheet(QStringLiteral("background-color: green;"));
    m_saveButton->setEnabled(false);

    m_imageLabel = new QLabel(this);

    m_frameBuffer = CreateFrameBuffer(DEFAULT_IMAGE_WIDTH, DEFAULT_IMAGE_HEIGHT);

    const float millisecondsInSecond = 1000.0f;
    m_renderTimer.setInterval(millisecondsInSecond / m_fps);

    connect(&m_renderTimer, &QTimer::timeout, this, [this]
    {
        RenderToFrameBuffer(m_frameBuffer, DEFAULT_IMAGE_WIDTH, DEFAULT_IMAGE_HEIGHT);
        m_image = CreateImageFromFrameBuffer(m_frameBuffer, DEFAULT_IMAGE_WIDTH, DEFAULT_IMAGE_HEIGHT);

        m_imageLabel->setPixmap(QPixmap::fromImage(m_image));
        m_saveButton->setEnabled(true);
    });

    connect(m_startButton, &QPushButton::clicked, this, [this]
    {
        m_renderTimer.start();
    });

    connect(m_saveButton, &QPushButton::clicked, this, [this]
    {
        QString currentTime = QDateTime::currentDateTime().toString(QStringLiteral("yyyy_MM_dd_hh_mm_ss_z"));

        if (!QDir(RESULT_IMAGES_DIRECTORY).exists())
        {
            QDir().mkdir(RESULT_IMAGES_DIRECTORY);
        }

        m_image.save(RESULT_IMAGES_DIRECTORY % QLatin1Char('/') % currentTime % RESULT_IMAGE_FILENAME);
    });

    m_sceneObjects.append(Sphere(0.3f, QVector3D(0, 0, -1.5), Material(QVector3D(128, 200, 40))));
    m_sceneObjects.append(Sphere(0.3f, QVector3D(1.0, 0, -1.5), Material(QVector3D(246, 56, 54))));
    m_sceneObjects.append(Sphere(0.3f, QVector3D(-0.2, 0.3, -2.5), Material(QVector3D(231, 32, 146))));
    m_sceneObjects.append(Sphere(0.3f, QVector3D(-1.0, 0, -3.5), Material(QVector3D(45, 235, 178))));

    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setAlignment(Qt::AlignHCenter);
    mainLayout->addWidget(m_imageLabel);
    mainLayout->addWidget(m_startButton);
    mainLayout->addWidget(m_saveButton);

    QRect desktopRect = QApplication::desktop()->availableGeometry(this);
    QPoint center = desktopRect.center();

    setGeometry(center.x() - DEFAULT_WINDOW_WIDTH * 0.5f,
                center.y() - DEFAULT_WINDOW_HEIGHT * 0.5f,
                DEFAULT_WINDOW_WIDTH,
                DEFAULT_WINDOW_HEIGHT);
    setWindowTitle(MAIN_WINDOW_TITLE);
}



QImage MainWindow::CreateImageFromFrameBuffer(const QVector<QVector3D>& frameBuffer,
                                              qint32 width, qint32 height) noexcept
{
    QImage image(width, height, QImage::Format_RGB32);
    QRgb currentValue;

    for (qint32 rowIndex = 0; rowIndex < height; ++rowIndex)
    {
        for (qint32 columnIndex = 0; columnIndex < width; ++columnIndex)
        {
            QVector3D pixel = frameBuffer[columnIndex + rowIndex * width];

            currentValue = qRgb(pixel[0], pixel[1], pixel[2]);
            image.setPixel(columnIndex, rowIndex, currentValue);
        }
    }

    return image;
}



QVector<QVector3D> MainWindow::CreateFrameBuffer(qint32 width, qint32 height) noexcept
{
    QVector<QVector3D> frameBuffer(width * height);

    return frameBuffer;
}



void MainWindow::RenderToFrameBuffer(QVector<QVector3D>& frameBuffer, qint32 width, qint32 height) const noexcept
{
    const float indentToPixelCenter = 0.5f;    // Половина пикселя.
    float screenWidth = 2.0f * qTan(m_fieldOfViewAngle * 0.5f) * m_screenCameraDistance;
    float screenHalfWidth = screenWidth * 0.5f;
    float screenAspectRatio = static_cast<float>(width) / static_cast<float>(height);

    for (qint32 rowIndex = 0; rowIndex < height; ++rowIndex)
    {
        for (qint32 columnIndex = 0; columnIndex < width; ++columnIndex)
        {
            float frameBufferPixelX = static_cast<float>(columnIndex);
            float frameBufferPixelY = static_cast<float>(rowIndex);    // Растёт в направлении, противоположном мировой оси OY.

            /* Эти координаты задаются в мировых единицах. Screen - плоскость в 3D-пространстве. */
            float screenPixelX =  ((frameBufferPixelX + indentToPixelCenter) / static_cast<float>(width) * screenWidth - screenHalfWidth) * screenAspectRatio;
            float screenPixelY = -((frameBufferPixelY + indentToPixelCenter) / static_cast<float>(height) * screenWidth - screenHalfWidth);

            Ray ray(m_cameraPosition,
                    QVector3D(screenPixelX, screenPixelY, -m_screenCameraDistance + m_cameraPosition.z()));

            frameBuffer[columnIndex + rowIndex * width] = CastRay(ray, m_sceneObjects);
        }
    }
}



QVector3D MainWindow::CastRay(const Ray& ray, const QVector<Sphere>& sceneObjects) const noexcept
{
    const qint32 sceneObjectsAmount = sceneObjects.size();
    Material resultMaterial(m_backgroundColor);
    QVector3D normal;
    float minIntersectionDistance = -1;
    bool wasAnyIntersection = false;

    for (qint32 i = 0; i < sceneObjectsAmount; ++i)
    {
        std::optional<float> optionalDistance = sceneObjects[i].CalcIntersectionDistance(ray);

        if (optionalDistance.has_value())
        {
            float distance = optionalDistance.value();

            if (distance <= m_distanceToTheFarClipPlane)
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
