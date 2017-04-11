#-------------------------------------------------
#
# Project created by QtCreator 2017-03-28T12:16:44
#
#-------------------------------------------------

QT       += xmlpatterns core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FlocksSimulator
TEMPLATE = app

CONFIG += c++11

HEADERS  += \
    src/ParameterSimulation.h \
    src/ThreadSimulator.h \
    src/DataLogger.h \
    src/BaseDefinition.h \
    src/DatabaseLogger.h \
    src/SimulatorsManager.h \
    src/gui/MainWindow.h \
    src/gui/AbstractPage.h \
    src/gui/ConfigSimulationPage.h \
    src/gui/FlocksConfigPage.h \
    src/gui/ObstaclesConfigPage.h \
    src/gui/StartSimulationPage.h \
    src/gui/SimulationInProgressPage.h \
    src/gui/LastPage.h \
    src/gui/DatabasePage.h

SOURCES += src/main.cpp \
    src/ParameterSimulation.cpp \
    src/ThreadSimulator.cpp \
    src/DatabaseLogger.cpp \
    src/SimulatorsManager.cpp \
    libs/include/jabs/altitudeCtrl.cpp \
    libs/include/jabs/anisotropicFlocking.cpp \
    libs/include/jabs/boidFlock.cpp \
    libs/include/jabs/boidNation.cpp \
    libs/include/jabs/boidRenderer.cpp \
    libs/include/jabs/boidSeek.cpp \
    libs/include/jabs/collAvoid.cpp \
    libs/include/jabs/flocking.cpp \
    libs/include/jabs/obstacleRenderer.cpp \
    libs/include/jabs/preBoidSeek.cpp \
    libs/include/jabs/preCollAvoid.cpp \
    libs/include/jabs/randomVal.cpp \
    libs/include/jabs/randomVec3.cpp \
    libs/include/jabs/simulation.cpp \
    src/gui/MainWindow.cpp \
    src/gui/AbstractPage.cpp \
    src/gui/ConfigSimulationPage.cpp \
    src/gui/FlokcsConfigPage.cpp \
    src/gui/ObstaclesConfigPage.cpp \
    src/gui/StartSimulationPage.cpp \
    src/gui/SimulationInProgressPage.cpp \
    src/gui/LastPage.cpp \
    src/gui/DatabasePage.cpp

INCLUDEPATH += $$PWD/libs/include
DEPENDPATH += $$PWD/libs/include

RESOURCES += \
    images.qrc \
    conf.qrc
