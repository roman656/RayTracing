#include <QApplication>

#include "View/MainWindow.hpp"

int main(int argc, char* argv[])
{
    QApplication application(argc, argv);
    QApplication::setFont(QFont(QStringLiteral("Roboto"), 16));

    MainWindow mainWindow;

    mainWindow.show();

    return application.exec();
}
