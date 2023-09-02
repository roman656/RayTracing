#include "MainWindow.hpp"

#include <QApplication>
#include <QDesktopWidget>
#include <QVBoxLayout>
#include <QDate>
#include <QStringBuilder>
#include <QDir>

#include "Render/Renderer.hpp"

MainWindow::MainWindow(QWidget* parent) noexcept : QMainWindow(parent)
{
    InitializeScene();

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
    m_imageLabel->setPixmap(QPixmap(DEFAULT_IMAGE_WIDTH, DEFAULT_IMAGE_HEIGHT));

    connect(m_saveButton, &QPushButton::clicked, this, &MainWindow::SaveImage);
    connect(m_startButton, &QPushButton::clicked, this, [this]
    {
        Renderer::Render(m_scene, m_frameBuffer);
        m_image = m_frameBuffer.CreateImage();

        m_imageLabel->setPixmap(QPixmap::fromImage(m_image));
        m_saveButton->setEnabled(true);
    });

    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setAlignment(Qt::AlignHCenter);
    mainLayout->addWidget(m_imageLabel);
    mainLayout->addWidget(m_startButton);
    mainLayout->addWidget(m_saveButton);

    const QRect desktopRect = QApplication::desktop()->availableGeometry(this);
    const QPoint center = desktopRect.center();

    setGeometry(center.x() - DEFAULT_WINDOW_WIDTH * 0.5f,
                center.y() - DEFAULT_WINDOW_HEIGHT * 0.5f,
                DEFAULT_WINDOW_WIDTH,
                DEFAULT_WINDOW_HEIGHT);
    setWindowTitle(MAIN_WINDOW_TITLE);
}



void MainWindow::InitializeScene() noexcept
{
    const float spheresSize = 0.3f;
    const Material redMaterial(QVector3D(255, 0, 0));    // Временное именование для различения сфер на сцене.
    const Material greenMaterial(QVector3D(0, 255, 0));
    const Material blueMaterial(QVector3D(0, 0, 255));
    const Material yellowMaterial(QVector3D(255, 255, 0));

    /* Стандартной камеры пока достаточно, поэтому явно не устанавливается. */
    m_scene.SetBackgroundColor(DEFAULT_BACKGROUND_COLOR);
    m_scene.AddLightPoint(LightPoint(QVector3D(-10, 10, 10)));
    m_scene.AddSphere(Sphere(spheresSize, QVector3D(0, 0, -1.5), redMaterial));
    m_scene.AddSphere(Sphere(spheresSize, QVector3D(-0.2, 0.3, -1.5), greenMaterial));
    m_scene.AddSphere(Sphere(spheresSize, QVector3D(-1.0, 0, -3.5), blueMaterial));
    m_scene.AddSphere(Sphere(spheresSize, QVector3D(1.0, 0, -1.5), yellowMaterial));
}



void MainWindow::SaveImage() const noexcept
{
    const QString currentTime = QDateTime::currentDateTime().toString(QStringLiteral("yyyy_MM_dd_hh_mm_ss_z"));

    if (!QDir(RESULT_IMAGES_DIRECTORY).exists())
    {
        QDir().mkdir(RESULT_IMAGES_DIRECTORY);
    }

    m_image.save(RESULT_IMAGES_DIRECTORY % QLatin1Char('/') % currentTime % RESULT_IMAGE_FILENAME);
}
