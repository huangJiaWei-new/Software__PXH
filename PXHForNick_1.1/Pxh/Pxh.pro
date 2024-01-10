QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

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

SOURCES += \
    camera/cameradialog.cpp \
    camera/cmvcamera.cpp \
    camera/mypicturewidget.cpp \
    findcenter/findrectcenterdlg.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    camera/cameradialog.h \
    camera/cmvcamera.h \
    camera/mypicturewidget.h \
    cmd_def.h \
    findcenter/findrectcenterdlg.h \
    mainwindow.h

FORMS += \
    camera/cameradialog.ui \
    findcenter/findrectcenterdlg.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


#---------------------------------opencv---------------------------------#
#MSVC
win32: LIBS += -LF:/Installation__path/Opencv/opencv-4.7.0-windows/opencv/build/x64/vc16/lib/ -lopencv_world470d

INCLUDEPATH += F:/Installation__path/Opencv/opencv-4.7.0-windows/opencv/build/include
DEPENDPATH += F:/Installation__path/Opencv/opencv-4.7.0-windows/opencv/build/include

#---------------------------------海康相机---------------------------------#
INCLUDEPATH += $$PWD/camera/Includes
DEPENDPATH += $$PWD/camera/Includes
LIBS += $$PWD/camera/Libraries/win64/MvCameraControl.lib

LIBS += User32.LIB
LIBS += -lGdi32


DISTFILES +=

RESOURCES += \
    Resources.qrc










