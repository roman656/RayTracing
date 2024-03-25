QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

SOURCES += \
    Render/Camera.cpp \
    Render/FrameBuffer.cpp \
    Render/LightPoint.cpp \
    Render/Material.cpp \
    Render/Ray.cpp \
    Render/Renderer.cpp \
    Render/Scene.cpp \
    Render/Sphere.cpp \
    main.cpp \
    View/MainWindow.cpp

HEADERS += \
    Config.hpp \
    Render/Camera.hpp \
    Render/FrameBuffer.hpp \
    Render/LightPoint.hpp \
    Render/Renderer.hpp \
    Render/Scene.hpp \
    View/MainWindow.hpp \
    Render/Material.hpp \
    Render/Ray.hpp \
    Render/Sphere.hpp

RESOURCES += \
    RayTracingResources.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
