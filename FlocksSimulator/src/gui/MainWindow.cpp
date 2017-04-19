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
    SimulationInProgressPage* sipPage = new SimulationInProgressPage();

    mPages.insert(AbstractPage::DATABASE,mDbPage);
    mPages.insert(AbstractPage::GENERAL_CONFIG,new ConfigSimulationPage());
    mPages.insert(AbstractPage::FLOCKS_CONFIG,new FlocksConfigPage());
    mPages.insert(AbstractPage::OBSTACLES_CONFIG,new ObstacleConfigPage());
    mPages.insert(AbstractPage::START_SIMULATION,new StartSimulationPage());
    mPages.insert(AbstractPage::SIMULATION_RUNNING,sipPage);
    mPages.insert(AbstractPage::RANDOM_SIM_PAGE, new RandomSimulationPage());
    mPages.insert(AbstractPage::LAST_PAGE,new LastPage());

    QList<AbstractPage*> pages = mPages.values();

    foreach (AbstractPage* page, pages) {
        this->addPage(page);
        connect(page, SIGNAL(nextPage(AbstractPage::PAGE_TYPE)),this,SLOT(pageChanged(AbstractPage::PAGE_TYPE)));
    }
    connect(&mSimulatorManager,SIGNAL(end()),this,SLOT(simulationsEnd()));
    connect(&mSimulatorManager,SIGNAL(message(QString)),sipPage,SLOT(readOutput(QString)));
    connect(&mSimulatorManager,SIGNAL(error(QString)),sipPage,SLOT(readError(QString)));

}

void MainWindow::toConfigPage()
{
    QList<AbstractPage*> pages = mPages.values();
    FlockSimulator::ParameterSimulation p;

    foreach (AbstractPage* page, pages) {
        page->setParameterSimulation(p,mSimulationParameter);
    }

    for(int i = 0; i < mSimulationParameter.length(); i++){
        mSimulatorManager.addSimulation(mSimulationParameter[i]);
    }

    mSimulationParameter.clear();

    while(currentId() != AbstractPage::GENERAL_CONFIG)
        back();
}

//void MainWindow::saveParameters()
//{
//    QList<AbstractPage*> pages = mPages.values();
//    FlockSimulator::ParameterSimulation p;

//    foreach (AbstractPage* page, pages) {
//        page->setParameterSimulation(p,mSimulationParameter);
//    }

////    mSimulationParameter.append(p);

////    if(mMultipleSimulationEnabled){

////    }
//}

void MainWindow::simulationsEnd()
{
    qDebug() << "ENDOO";
    button(QWizard::BackButton)->setDisabled(false);
    button(QWizard::NextButton)->setDisabled(false);
    next();
}

void MainWindow::pageChanged(AbstractPage::PAGE_TYPE type)
{
    if(AbstractPage::START_SIMULATION == type){
       disconnect(button(QWizard::CancelButton),SIGNAL(clicked()),this,SLOT(reject()));
       connect(button(QWizard::CancelButton),SIGNAL(clicked()),this,SLOT(toConfigPage()));
    }
    if(AbstractPage::OBSTACLES_CONFIG==type || AbstractPage::SIMULATION_RUNNING == type){
       disconnect(button(QWizard::CancelButton),SIGNAL(clicked()),this,SLOT(toConfigPage()));
       connect(button(QWizard::CancelButton),SIGNAL(clicked()),this,SLOT(reject()));
    }

    if(AbstractPage::SIMULATION_RUNNING == type){

        QList<AbstractPage*> pages = mPages.values();
        FlockSimulator::ParameterSimulation p;

        foreach (AbstractPage* page, pages) {
            page->setParameterSimulation(p,mSimulationParameter);
        }

        mSimulatorManager.setDataLogger(mSelectedLogger);
        mSimulatorManager.setMaxParallelThread(4);

        for(int i = 0; i < mSimulationParameter.length(); i++){
            mSimulatorManager.addSimulation(mSimulationParameter[i]);
        }
//        mDbLogger->closeConnection();
        mSimulatorManager.startSimulations();
    }
}

void MainWindow::nextButtonPressed()
{
//    emit next();
}
