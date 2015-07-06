#-------------------------------------------------
#
# Project created by QtCreator 2015-05-07T11:11:02
#
#-------------------------------------------------


greaterThan(QT_MAJOR_VERSION, 4):

QT += core gui network webkitwidgets printsupport

TARGET = SampleIDViewer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    sampleidlistmodel.cpp \
    sampleidlistwidget.cpp \
    qcustomplot.cpp \
    abifreader.cpp \
    fsainfowidget.cpp \
    sampleidinfowidget.cpp \
    networkmanager.cpp \
    tools.cpp \
    filebrowserwidget.cpp \
    fsaplot.cpp \
    fsaviewer.cpp \
    fsapanelwidget.cpp

HEADERS  += mainwindow.h \
    sampleidlistmodel.h \
    sampleidlistwidget.h \
    qcustomplot.h \
    abifreader.h \
    fsainfowidget.h \
    sampleidinfowidget.h \
    networkmanager.h \
    tools.h \
    filebrowserwidget.h \
    fsaplot.h \
    fsaviewer.h \
    fsapanelwidget.h

FORMS    += mainwindow.ui

RESOURCES += \
    icons.qrc
