#include "StartSimulationPage.h"

StartSimulationPage::StartSimulationPage()
    :AbstractPage(START_SIMULATION)
{
    this->setTitle("Start Simulation");

    setButtonText(QWizard::NextButton,QString("Start"));

}

int StartSimulationPage::nextId() const
{
    emit nextPage(PAGE_TYPE::SIMULATION_RUNNING);
    return PAGE_TYPE::SIMULATION_RUNNING;
}
