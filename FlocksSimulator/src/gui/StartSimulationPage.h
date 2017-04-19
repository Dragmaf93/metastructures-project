#ifndef STARTSIMULATIONPAGE_H
#define STARTSIMULATIONPAGE_H

#include"AbstractPage.h"

class StartSimulationPage: public AbstractPage{
    Q_OBJECT
public:
    StartSimulationPage();

    void setParameterSimulation(FlockSimulator::ParameterSimulation &parameter,QVector<FlockSimulator::ParameterSimulation>& pVector){}
    int nextId()const;
    void initializePage();
    void cleanupPage();

};
#endif // STARTSIMULATIONPAGE_H
