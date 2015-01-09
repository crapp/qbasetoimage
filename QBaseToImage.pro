#-------------------------------------------------
#
# Project created by QtCreator 2012-07-04T21:46:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++11

TARGET = QBaseToImage
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    previewdialog.cpp \
    filesaveoperation.cpp \
    createimage.cpp

HEADERS  += mainwindow.h \
    previewdialog.h \
    qticon.h \
    filesaveoperation.h \
    createimage.h

FORMS    += mainwindow.ui \
    previewdialog.ui
