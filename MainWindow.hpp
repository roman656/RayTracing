#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QImage>
#include <QtMath>
#include <QTimer>

#include "Sphere.hpp"

class MainWindow final : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr) noexcept;

private:
    Q_DISABLE_COPY_MOVE(MainWindow)

    static QVector<QVector3D> CreateFrameBuffer(qint32 width, qint32 height) noexcept;
    static QImage CreateImageFromFrameBuffer(const QVector<QVector3D>& frameBuffer,
                                             qint32 width, qint32 height) noexcept;

    void RenderToFrameBuffer(QVector<QVector3D>& frameBuffer, qint32 width, qint32 height) const noexcept;
    QVector3D CastRay(const Ray& ray, const QVector<Sphere>& sceneObjects) const noexcept;

    QVector3D m_backgroundColor = QVector3D(128.0f, 128.0f, 128.0f);
    QVector<QVector3D> m_frameBuffer;
    QVector3D m_cameraPosition = QVector3D(0.0f, 0.0f, 0.0f);
    float m_screenCameraDistance = 1.0f;    // distanceToTheNearClipPlane
    float m_distanceToTheFarClipPlane = 1000.0f;
    float m_fieldOfViewAngle = qDegreesToRadians(90.0f);
    float m_fps = 30.0f;
    QVector<Sphere> m_sceneObjects;

    QTimer m_renderTimer;
    QImage m_image;
    QLabel* m_imageLabel = nullptr;
    QPushButton* m_startButton = nullptr;
    QPushButton* m_saveButton = nullptr;
};

#endif // MAINWINDOW_HPP
