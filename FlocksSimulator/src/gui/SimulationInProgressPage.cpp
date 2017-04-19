#include "SimulationInProgressPage.h"

SimulationInProgressPage::SimulationInProgressPage()
    :AbstractPage(SIMULATION_RUNNING)
{
    this->setTitle("Simulation in progress");

    QVBoxLayout* rootLayout = new QVBoxLayout;


    mTextEdit = new QTextEdit;
    rootLayout->addWidget(mTextEdit);

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

void SimulationInProgressPage::readOutput(QString string)
{
    mTextEdit->append(string);
}

void SimulationInProgressPage::readError(QString string)
{
    mTextEdit->append(string);
}
