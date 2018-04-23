#-------------------------------------------------
#
# Project created by QtCreator 2018-01-18T18:58:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = text
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    updatedialog.cpp

HEADERS  += mainwindow.h \
    updatedialog.h

FORMS    += mainwindow.ui \
    updatedialog.ui

RESOURCES += \
    res.qrc
RC_FILE = myapp.rc
