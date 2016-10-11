#-------------------------------------------------
#
# Project created by QtCreator 2016-09-27T04:17:30
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtJournal
TEMPLATE = app
CONFIG   -= x86_64

SOURCES += main.cpp\
    localapi.cpp \
    journalmodel.cpp \
    entrymodel.cpp

HEADERS  += localapi.h \
    journalmodel.h \
    entrymodel.h \
    main.h

RESOURCES += README.md \
           LICENSE.md

FORMS    += mainwindow.ui
