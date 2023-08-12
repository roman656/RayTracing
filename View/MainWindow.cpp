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
    m_scene.SetBackgroundColor(DEFAULT_BACKGROUND_COLOR);
    m_scene.SetCamera(Camera());
    m_scene.AddSphere(Sphere(0.3f, QVector3D(0, 0, -1.5), Material(QVector3D(128, 200, 40))));
    m_scene.AddSphere(Sphere(0.3f, QVector3D(1.0, 0, -1.5), Material(QVector3D(246, 56, 54))));
    m_scene.AddSphere(Sphere(0.3f, QVector3D(-0.2, 0.3, -2.5), Material(QVector3D(231, 32, 146))));
    m_scene.AddSphere(Sphere(0.3f, QVector3D(-1.0, 0, -3.5), Material(QVector3D(45, 235, 178))));

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

    QRect desktopRect = QApplication::desktop()->availableGeometry(this);
    QPoint center = desktopRect.center();

    setGeometry(center.x() - DEFAULT_WINDOW_WIDTH * 0.5f,
                center.y() - DEFAULT_WINDOW_HEIGHT * 0.5f,
                DEFAULT_WINDOW_WIDTH,
                DEFAULT_WINDOW_HEIGHT);
    setWindowTitle(MAIN_WINDOW_TITLE);
}



void MainWindow::SaveImage() const noexcept
{
    QString currentTime = QDateTime::currentDateTime().toString(QStringLiteral("yyyy_MM_dd_hh_mm_ss_z"));

    if (!QDir(RESULT_IMAGES_DIRECTORY).exists())
    {
        QDir().mkdir(RESULT_IMAGES_DIRECTORY);
    }

    m_image.save(RESULT_IMAGES_DIRECTORY % QLatin1Char('/') % currentTime % RESULT_IMAGE_FILENAME);
}
