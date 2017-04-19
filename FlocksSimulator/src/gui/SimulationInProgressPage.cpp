#include "SimulationInProgressPage.h"

SimulationInProgressPage::SimulationInProgressPage()
    :AbstractPage(SIMULATION_RUNNING)
{
    this->setTitle("Simulation in progress");

    QVBoxLayout* rootLayout = new QVBoxLayout;

    mTextEdit = new QTextEdit;
    mTextEdit->setReadOnly(true);
    rootLayout->addWidget(mTextEdit);

    mProgressBar = new QProgressBar;

    rootLayout->addWidget(mProgressBar);

    mSimulationEnded = false;
    this->setLayout(rootLayout);
}

void SimulationInProgressPage::initializePage()
{
    AbstractPage::initializePage();
    emit nextPage(PAGE_TYPE::SIMULATION_RUNNING);
}

int SimulationInProgressPage::nextId() const
{
    return LAST_PAGE;
}

bool SimulationInProgressPage::isComplete() const
{
    return mSimulationEnded;
}

void SimulationInProgressPage::simulationsStarted()
{
    mProgressBar->setMaximum(mSimulator->getMaximumProgress()+ mSimulator->getMaximumProgress()*0.01);

    qDebug() << mProgressBar->maximum();
}

void SimulationInProgressPage::setSimulator(FlockSimulator::SimulatorsManager &s)
{
   mSimulator = &s;
   connect(mSimulator,SIGNAL(progress(int)),mProgressBar,SLOT(setValue(int)));
}

void SimulationInProgressPage::simulationEnded()
{
    mSimulationEnded=true;
    mProgressBar->setValue(mProgressBar->maximum());
}

void SimulationInProgressPage::readOutput(QString string)
{
    mTextEdit->append(string);
}

void SimulationInProgressPage::readError(QString string)
{
    mTextEdit->append(string);
}

void SimulationInProgressPage::updateProgressBar()
{
    while(mSimulationEnded){
        mProgressBar->setValue(mSimulator->getProgress());
        QThread::sleep(2);
    }
    mProgressBar->setValue(mProgressBar->maximum());
}
