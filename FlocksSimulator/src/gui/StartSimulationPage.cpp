#include "StartSimulationPage.h"

StartSimulationPage::StartSimulationPage()
    :AbstractPage(START_SIMULATION)
{
    this->setTitle("Start Simulation");

    setButtonText(QWizard::NextButton,QString("Start"));
}
