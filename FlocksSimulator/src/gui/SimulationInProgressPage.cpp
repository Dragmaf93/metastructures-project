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
    ProgressBarUpdater* thread = new ProgressBarUpdater(this);
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}

void SimulationInProgressPage::setSimulator(FlockSimulator::SimulatorsManager &s)
{
   mSimulator = &s;
}

void SimulationInProgressPage::simulationEnded()
{
    mSimulationEnded=true;
}

void SimulationInProgressPage::readOutput(QString string)
{
    mTextEdit->append(string);
}

void SimulationInProgressPage::readError(QString string)
{
    mTextEdit->append(string);
}

ProgressBarUpdater::ProgressBarUpdater(SimulationInProgressPage *p)
{
    this->page = p;
}

void ProgressBarUpdater::run()
{
    while(!page->mSimulationEnded){
        page->mProgressBar->setValue(page->mSimulator->getProgress());
        QThread::sleep(2);
    }
    page->mProgressBar->setValue(page->mProgressBar->maximum());
}
