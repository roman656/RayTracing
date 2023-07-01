#include <QApplication>

#include "MainWindow.hpp"
#include "Config.hpp"

int main(int argc, char* argv[])
{
    QApplication application(argc, argv);
    MainWindow mainWindow;

    QApplication::setFont(MAIN_FONT);

    mainWindow.show();

    return application.exec();
}
