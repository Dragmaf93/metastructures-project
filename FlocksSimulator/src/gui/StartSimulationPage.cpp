#include "StartSimulationPage.h"

StartSimulationPage::StartSimulationPage()
    :AbstractPage(START_SIMULATION)
{
    this->setTitle("Start Simulation");

    setButtonText(QWizard::NextButton,QString("Start"));

    setButtonText(QWizard::CancelButton,QString("Continue to add simulations"));
}

int StartSimulationPage::nextId() const
{
    return PAGE_TYPE::SIMULATION_RUNNING;
}

void StartSimulationPage::initializePage()
{
    AbstractPage::initializePage();
    emit nextPage(START_SIMULATION);
}

void StartSimulationPage::cleanupPage()
{
    AbstractPage::cleanupPage();
    emit nextPage(OBSTACLES_CONFIG);
}
