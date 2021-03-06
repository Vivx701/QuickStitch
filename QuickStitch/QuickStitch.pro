#-------------------------------------------------
#
# Project created by QtCreator 2018-10-22T22:01:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QuickStitch
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
    imagestitcher.cpp \
    quickstitchwindow.cpp \
    stitchdialog.cpp \
    about.cpp

HEADERS += \
    imagestitcher.h \
    quickstitchwindow.h \
    stitchdialog.h \
    about.h \
    strings.h

FORMS += \
    quickstitchwindow.ui \
    stitchdialog.ui \
    about.ui

RESOURCES += \
    resources.qrc


unix {

    #VARIABLES
    isEmpty(PREFIX) {
        PREFIX = /usr
    }
    BINDIR = $$PREFIX/bin
    DATADIR =$$PREFIX/share


    target.path =$$BINDIR
    INSTALLS += target

    icon.path = $$DATADIR/icons/hicolor/scalable/apps
    icon.files += ./data/icons/$${TARGET}.svg
    INSTALLS += icon

    desktop.path = $$DATADIR/applications
    desktop.files += ./data/$${TARGET}.desktop
    INSTALLS += desktop
}
