#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>

#include "Render/FrameBuffer.hpp"
#include "Render/Scene.hpp"
#include "Config.hpp"

class MainWindow final : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr) noexcept;

private:
    Q_DISABLE_COPY_MOVE(MainWindow)

    void InitializeScene() noexcept;
    void SaveImage() const noexcept;

    FrameBuffer m_frameBuffer = FrameBuffer(DEFAULT_IMAGE_WIDTH, DEFAULT_IMAGE_HEIGHT);
    Scene m_scene;

    QImage m_image;
    QLabel* m_imageLabel = nullptr;
    QPushButton* m_startButton = nullptr;
    QPushButton* m_saveButton = nullptr;
};

#endif // MAINWINDOW_HPP
