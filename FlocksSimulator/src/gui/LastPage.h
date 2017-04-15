#ifndef LASTPAGE_H
#define LASTPAGE_H

#include"AbstractPage.h"

class LastPage: public AbstractPage{
    Q_OBJECT

public:
    LastPage();
    void setParameterSimulation(FlockSimulator::ParameterSimulation &parameter,QVector<FlockSimulator::ParameterSimulation>& pVector){}

};

#endif // LASTPAGE_H
