#-------------------------------------------------
#
# Project created by QtCreator 2020-11-30T23:58:41
#
#-------------------------------------------------

QT       += testlib
#QT       -= gui

TARGET = tst_statisticstest
CONFIG   += console
CONFIG   -= app_bundle

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
        tst_statisticstest.cpp \
        ../Game/statistics.cpp \
        ../Course/CourseLib/errors/gameerror.cc \
        ../Course/CourseLib/errors/initerror.cc

HEADERS += ../Game/statistics.h \
           ../Course/CourseLib/interfaces/istatistics.hh \
           ../Course/CourseLib/errors/gameerror.hh \
           ../Course/CourseLib/errors/initerror.hh \

DEFINES += SRCDIR=\\\"$$PWD/\\\"

INCLUDEPATH += ../Game/ \
               ../Course/CourseLib/

DEPENDPATH += ../Game/ \
              ../Course/CourseLib/
