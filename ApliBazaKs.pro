#-------------------------------------------------
#
# Project created by QtCreator 2012-03-09T12:05:22
#
#-------------------------------------------------

QT       += core gui sql script
QMAKE_CXXFLAGS += -std=c++17

TARGET = ApliBazaKs
TEMPLATE = app
SOURCES += main.cpp\
        mainwindow.cpp \
    logindialog.cpp \
    xmlreader.cpp \
    sharedtypes.cpp \
    baza.cpp \
    akcja.cpp

HEADERS  += mainwindow.h \
    baza.h \
    logindialog.h \
    xmlreader.h \
    sharedtypes.h \
    akcja.h \
    objects.h

FORMS    += mainwindow.ui \
    logindialog.ui
