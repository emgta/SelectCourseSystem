#-------------------------------------------------
#
# Project created by QtCreator 2019-12-02T19:03:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CoursePlatform
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    Client/user_interface.cpp \
    Graphic/info_to_str.cpp \
    Graphic/ipaddlogin.cpp \
    Graphic/login.cpp \
    Graphic/main.cpp \
    Graphic/registerdialog.cpp \
    Graphic/stu_cancel.cpp \
    Graphic/stu_check.cpp \
    Graphic/stu_percheck.cpp \
    Graphic/stu_select.cpp \
    Graphic/studentmain.cpp \
    Graphic/tea_change.cpp \
    Graphic/tea_check.cpp \
    Graphic/tea_percheck.cpp \
    Graphic/teachermain.cpp \
    Shared/socket_fun.cpp \
    Shared/global.cpp \
    Shared/network.cpp \
    Graphic/graphic_client_interface.cpp

HEADERS += \
    Client/user_interface.hpp \
    Graphic/info_to_str.h \
    Graphic/ipaddlogin.h \
    Graphic/login.h \
    Graphic/registerdialog.h \
    Graphic/stu_cancel.h \
    Graphic/stu_check.h \
    Graphic/stu_percheck.h \
    Graphic/stu_select.h \
    Graphic/studentmain.h \
    Graphic/tea_change.h \
    Graphic/tea_check.h \
    Graphic/tea_percheck.h \
    Graphic/teachermain.h \
    Shared/global.hpp \
    Shared/network.hpp \
    Graphic/graphic_client_interface.hpp \
    Shared/socket_fun.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    Graphic/ipaddlogin.ui \
    Graphic/login.ui \
    Graphic/registerdialog.ui \
    Graphic/stu_cancal.ui \
    Graphic/stu_check.ui \
    Graphic/stu_percheck.ui \
    Graphic/stu_select.ui \
    Graphic/studentmain.ui \
    Graphic/tea_change.ui \
    Graphic/tea_check.ui \
    Graphic/tea_percheck.ui \
    Graphic/teachermain.ui

LIBS += -lws2_32

RESOURCES += \
    image.qrc
