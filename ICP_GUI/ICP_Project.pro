#-------------------------------------------------
#
# Project created by QtCreator 2018-04-26T10:21:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ICP_Project
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


SOURCES += \
    src/gui/connection.cpp \
    src/gui/icp_gui.cpp \
    src/gui/node.cpp \
    src/gui/port.cpp \
    src/gui/style.cpp \
    src/gui/tooltip.cpp \
    src/main.cpp \
    src/core/type.cpp

HEADERS += \
    src/gui/connection.h \
    src/gui/icp_gui.h \
    src/gui/node.h \
    src/gui/port.h \
    src/gui/style.h \
    src/gui/tooltip.h \
    src/core/type.h

FORMS += \
    src/gui/icp_gui.ui
