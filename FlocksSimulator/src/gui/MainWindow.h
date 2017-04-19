#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMap>
#include<QMessageBox>
#include<QWizard>

#include"AbstractPage.h"
#include "ConfigSimulationPage.h"
#include "MainWindow.h"
#include "FlocksConfigPage.h"
#include "ObstaclesConfigPage.h"
#include "StartSimulationPage.h"
#include "SimulationInProgressPage.h"
#include "LastPage.h"
#include "DatabasePage.h"
#include "RandomSimulationPage.h"
#include "../MessageSender.h"
#include"../SimulatorsManager.h"
#include"../DatabaseLogger.h"

class MainWindow : public QWizard{
    Q_OBJECT

public:
    MainWindow(QWidget* parent=nullptr);

private:
    QMap<AbstractPage::PAGE_TYPE,AbstractPage*> mPages;
    FlockSimulator::SimulatorsManager mSimulatorManager;

    QVector<FlockSimulator::ParameterSimulation> mSimulationParameter;
    bool mMultipleSimulationEnabled;

    FlockSimulator::DatabaseLogger* mDbLogger;
    FlockSimulator::DataLogger* mSelectedLogger;

    DatabasePage* mDbPage;
    SimulationInProgressPage* mSipPage;
signals:
    void nextPage();

private slots:
    void toConfigPage();
    void simulationsEnd();
    void pageChanged(AbstractPage::PAGE_TYPE);
    void nextButtonPressed();
};
#endif // MAINWINDOW_H
