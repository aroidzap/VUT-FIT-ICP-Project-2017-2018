#-------------------------------------------------
#
# Project created by QtCreator 2018-04-26T10:21:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = blockeditor
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
    src/gui/style.cpp \
    src/gui/tooltip.cpp \
    src/main.cpp \
    src/core/type.cpp \
    src/core/port.cpp \
    src/core/blockbase.cpp \
    src/core/blocks/vectoraddblock.cpp \
    src/core/blocks/vector_io.cpp \
    src/gui/connection_ui.cpp \
    src/gui/port_ui.cpp \
    src/gui/blockeditor.cpp \
    src/core/graph.cpp \
    src/core/xml.cpp \
    src/core/types/types.cpp \
    src/core/blockfactory.cpp \
    src/gui/blockfactory_ui.cpp \
    src/gui/graph_ui.cpp \
    src/core/blocks/vectordotproductblock.cpp \
    src/core/blocks/scalaraddblock.cpp \
    src/core/blocks/matrixmulblock.cpp \
    src/core/blocks/matrixaddblock.cpp \
    src/core/blocks/scalarsubblock.cpp \
    src/core/blocks/scalarmulblock.cpp \
    src/core/blocks/scalar_io.cpp \
    src/core/blocks/matrix_io.cpp \
    src/gui/alert.cpp

HEADERS += \
    src/gui/style.h \
    src/gui/tooltip.h \
    src/core/type.h \
    src/core/port.h \
    src/core/blockbase.h \
    src/core/blocks/vectoraddblock.h \
    src/core/blocks/vector_io.h \
    src/gui/connection_ui.h \
    src/gui/block_ui.h \
    src/gui/port_ui.h \
    src/gui/blockeditor.h \
    src/core/graph.h \
    src/core/xml.h \
    src/core/types/types.h \
    src/core/blockfactory.h \
    src/core/blocks.h \
    src/gui/blockfactory_ui.h \
    src/gui/graph_ui.h \
    src/core/blocks/vectordotproductblock.h \
    src/core/blocks/scalaraddblock.h \
    src/core/blocks/matrixaddblock.h \
    src/core/blocks/matrixmulblock.h \
    src/core/blocks/scalarsubblock.h \
    src/core/blocks/scalarmulblock.h \
    src/core/blocks/scalar_io.h \
    src/core/blocks/matrix_io.h \
    src/gui/alert.h

FORMS += \
    src/gui/blockeditor.ui

QMAKE_CXXFLAGS += -std=c++14
