QT += core gui
QT += multimedia #���ֲ���

RC_ICONS = logo.ico

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

HEADERS += \
    Bullet.h \
    EnemyPlane.h \
    MyPlane.h \
    Plane.h \
    Object.h \
    Scene.h \
    Config.h \
    ProcessGame.h \
    MyView.h \
    Medicine.h

SOURCES += \
    Bullet.cpp \
    EnemyPlane.cpp \
    main.cpp \
    MyPlane.cpp \
    Plane.cpp \
    Object.cpp \
    Scene.cpp \
    ProcessGame.cpp \
    MyView.cpp \
    Medicine.cpp

CONFIG += C++11

RESOURCES += \
    resources.qrc

DISTFILES +=

TARGET = FireOnGalaxy
