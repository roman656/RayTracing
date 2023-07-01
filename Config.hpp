#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <QString>
#include <QFont>

const QString MAIN_WINDOW_TITLE(QStringLiteral("RayTracing"));
const QString RESULT_IMAGES_DIRECTORY(QStringLiteral("ResultImages"));
const QString RESULT_IMAGE_FILENAME(QStringLiteral("_RayTracing.png"));
const qint32 DEFAULT_WINDOW_WIDTH = 600;
const qint32 DEFAULT_WINDOW_HEIGHT = 400;
const qint32 DEFAULT_IMAGE_WIDTH = 300;
const qint32 DEFAULT_IMAGE_HEIGHT = 300;
const qint32 ICON_SIZE = 35;
const qint32 MAX_COLOR_VALUE = 255;
const QFont MAIN_FONT(QStringLiteral("Arial"), 16);

#endif // CONFIG_HPP
