#include "FrameBuffer.hpp"

#include <QImage>

FrameBuffer::FrameBuffer(qint32 width, qint32 height) noexcept
{
    m_width = width;
    m_height = height;
    m_data.resize(m_width * m_height);
}



qint32 FrameBuffer::GetWidth() const noexcept
{
    return m_width;
}



qint32 FrameBuffer::GetHeight() const noexcept
{
    return m_height;
}



void FrameBuffer::SetPixel(qint32 rowIndex, qint32 columnIndex, const QVector3D& pixelColor) noexcept
{
    m_data[columnIndex + rowIndex * m_width] = pixelColor;
}



QVector3D FrameBuffer::GetPixel(qint32 rowIndex, qint32 columnIndex) const noexcept
{
    return m_data[columnIndex + rowIndex * m_width];
}



QImage FrameBuffer::CreateImage() const noexcept
{
    QImage image(m_width, m_height, QImage::Format_RGB32);
    QRgb currentPixelColor;

    for (qint32 rowIndex = 0; rowIndex < m_height; ++rowIndex)
    {
        for (qint32 columnIndex = 0; columnIndex < m_width; ++columnIndex)
        {
            const QVector3D pixel = GetPixel(rowIndex, columnIndex);

            currentPixelColor = qRgb(pixel[0], pixel[1], pixel[2]);
            image.setPixel(columnIndex, rowIndex, currentPixelColor);
        }
    }

    return image;
}
