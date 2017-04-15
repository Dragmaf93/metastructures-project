#ifndef STARTSIMULATIONPAGE_H
#define STARTSIMULATIONPAGE_H

#include"AbstractPage.h"

class StartSimulationPage: public AbstractPage{
    Q_OBJECT
public:
    StartSimulationPage();
    void setParameterSimulation(FlockSimulator::ParameterSimulation &parameter,QVector<FlockSimulator::ParameterSimulation>& pVector){}
    int nextId()const;
};
#endif // STARTSIMULATIONPAGE_H
