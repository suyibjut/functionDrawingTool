#-------------------------------------------------
#
# Project created by QtCreator 2018-08-27T14:52:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = draw_function
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
        main.cpp \
        mainwindow.cpp \
    qcustomplot.cpp \
    dialogaddfuntion.cpp \
    dialogdraw.cpp \
    function1.cpp \
    function2.cpp \
    analyse_function.cpp \
    calculate_debug.cpp

HEADERS += \
        mainwindow.h \
    qcustomplot.h \
    dialogaddfuntion.h \
    dialogdraw.h \
    function1.h \
    function2.h

FORMS += \
        mainwindow.ui \
    dialogaddfuntion.ui \
    dialogdraw.ui
