#include "MainWindow.h"
#include<QDebug>

MainWindow::MainWindow(QWidget* parent)
    :QWizard(parent)
{
    mMultipleSimulationEnabled = false;

    mDbLogger = new FlockSimulator::DatabaseLogger();
    mSelectedLogger = mDbLogger;

    mDbPage = new DatabasePage();
    mDbPage->setDatabaseLogger(mDbLogger);

    mPages.insert(AbstractPage::DATABASE,mDbPage);
    mPages.insert(AbstractPage::GENERAL_CONFIG,new ConfigSimulationPage());
    mPages.insert(AbstractPage::FLOCKS_CONFIG,new FlocksConfigPage());
    mPages.insert(AbstractPage::OBSTACLES_CONFIG,new ObstacleConfigPage());
    mPages.insert(AbstractPage::START_SIMULATION,new StartSimulationPage());
    mPages.insert(AbstractPage::SIMULATION_RUNNING,new SimulationInProgressPage());
    mPages.insert(AbstractPage::LAST_PAGE,new LastPage());

    QList<AbstractPage*> pages = mPages.values();

    foreach (AbstractPage* page, pages) {
        this->addPage(page);
        connect(page,SIGNAL(nextPage(AbstractPage::PAGE_TYPE)),this,SLOT(pageChanged(AbstractPage::PAGE_TYPE)));
    }

    connect(&mSimulatorManager,SIGNAL(end()),this,SLOT(simulationsEnd()));
}

void MainWindow::saveParameters()
{
    QList<AbstractPage*> pages = mPages.values();
    FlockSimulator::ParameterSimulation p;

    foreach (AbstractPage* page, pages) {
        page->setParameterSimulation(p);
    }

    mSimulationParameter.append(p);

    if(mMultipleSimulationEnabled){

    }
}

void MainWindow::simulationsEnd()
{
    qDebug() << "ENDOO";
    button(QWizard::BackButton)->setDisabled(false);
    button(QWizard::NextButton)->setDisabled(false);
    next();
}

void MainWindow::pageChanged(AbstractPage::PAGE_TYPE type)
{
    if(AbstractPage::SIMULATION_RUNNING == type){
        saveParameters();

        button(QWizard::BackButton)->setDisabled(true);
        button(QWizard::NextButton)->setDisabled(true);
        startSimulations();
    }

    if(AbstractPage::GENERAL_CONFIG == type){

        mDbPage->setDatabase();
        if(!mDbLogger->testConnection()){
            QMessageBox::critical(this,"Error","Can't connect to database.",QMessageBox::Ok);
        }else{

        }
    }

}

void MainWindow::nextButtonPressed()
{
    emit next();
}

void MainWindow::startSimulations()
{
    mSimulatorManager.setDataLogger(mSelectedLogger);
    mSimulatorManager.setMaxParallelThread(4);

    for(int i = 0; i < mSimulationParameter.length(); i++){
        mSimulatorManager.addSimulation(mSimulationParameter[i]);
    }

    mSimulatorManager.startSimulations();
}