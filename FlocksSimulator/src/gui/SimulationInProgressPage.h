#ifndef SIMULATIONINPROGRESSPAGE_H
#define SIMULATIONINPROGRESSPAGE_H

#include"AbstractPage.h"
class SimulationInProgressPage: public AbstractPage{
    Q_OBJECT
public:
    SimulationInProgressPage();
    void setParameterSimulation(FlockSimulator::ParameterSimulation &parameter){}
};

#endif // SIMULATIONINPROGRESSPAGE_H
