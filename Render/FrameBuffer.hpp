#ifndef FRAMEBUFFER_HPP
#define FRAMEBUFFER_HPP

#include <QVector3D>
#include <QVector>

class FrameBuffer final
{
public:
    explicit FrameBuffer(qint32 width, qint32 height) noexcept;

    qint32 GetWidth() const noexcept;
    qint32 GetHeight() const noexcept;

    void SetPixel(qint32 rowIndex, qint32 columnIndex, const QVector3D& pixelColor) noexcept;

    QImage CreateImage() const noexcept;

private:
    QVector3D GetPixel(qint32 rowIndex, qint32 columnIndex) const noexcept;

    qint32 m_width;
    qint32 m_height;
    QVector<QVector3D> m_data;
};

#endif // FRAMEBUFFER_HPP
