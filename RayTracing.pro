QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    Material.cpp \
    Ray.cpp \
    Sphere.cpp \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    Config.hpp \
    MainWindow.hpp \
    Material.hpp \
    Ray.hpp \
    Sphere.hpp

RESOURCES += \
    RayTracingResources.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
