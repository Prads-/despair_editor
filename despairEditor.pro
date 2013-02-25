#-------------------------------------------------
#
# Project created by QtCreator 2013-01-11T12:10:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = despairEditor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    SourceTreeWidget.cpp \
    SourceTreeItem.cpp \
    SourcePlainText.cpp \
    ProjectManager.cpp \
    FrmNewSource.cpp \
    FrmAddFolder.cpp \
    FrmAbout.cpp \
    FrmNewProject.cpp \
    FrmFindAndReplace.cpp \
    FrmFrameLength.cpp \
    FrmCompilerError.cpp \
    FrmMemorySize.cpp

HEADERS  += mainwindow.h \
    SourceTreeWidget.h \
    SourceTreeItem.h \
    SourcePlainText.h \
    ProjectManager.h \
    FrmNewSource.h \
    FrmAddFolder.h \
    FrmAbout.h \
    FrmNewProject.h \
    FrmFindAndReplace.h \
    FrmFrameLength.h \
    FrmCompilerError.h \
    FrmMemorySize.h

FORMS    += mainwindow.ui \
    frmNewSource.ui \
    FrmAddFolder.ui \
    FrmAbout.ui \
    FrmNewProject.ui \
    FrmFindAndReplace.ui \
    FrmFrameLength.ui \
    FrmCompilerError.ui \
    FrmMemorySize.ui

RESOURCES += \
    icons.qrc
