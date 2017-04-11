#ifndef LASTPAGE_H
#define LASTPAGE_H

#include"AbstractPage.h"

class LastPage: public AbstractPage{
    Q_OBJECT

public:
    LastPage();
    void setParameterSimulation(FlockSimulator::ParameterSimulation &parameter){}

};

#endif // LASTPAGE_H
