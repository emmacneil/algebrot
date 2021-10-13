QT += core gui widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

TARGET = algebrot

SOURCES += \
        src/fractal_widget.cpp \
        src/main.cpp \
        src/mainwindow.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH = include/
HEADERS += \
    include/fractal_widget.hpp \
    include/mainwindow.hpp

OBJECTS_DIR = build
MOC_DIR = build

DISTFILES += \
    glsl/algebrot2d.frag \
    glsl/algebrot3d.frag

RESOURCES += \
    resources.qrc
