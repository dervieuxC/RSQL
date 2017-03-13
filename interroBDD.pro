#-------------------------------------------------
#
# Project created by QtCreator 2017-02-27T09:02:40
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = interroBDD
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    accueil.cpp

HEADERS  += mainwindow.h \
    accueil.h

FORMS    += mainwindow.ui \
    accueil.ui
TRANSLATIONS  += interroBDD_fr_FR.ts \ interroBDD_de.ts

RESOURCES += \
    ressource/ressource.qrc
