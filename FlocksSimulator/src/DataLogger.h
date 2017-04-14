#ifndef DATALOGGER_H
#define DATALOGGER_H

#include<jabs/jabs.hpp>
#include"parametersimulation.h"

#include<QString>
#include<QObject>
namespace  FlockSimulator {

class DataLogger : public QObject{
    Q_OBJECT
public:
    virtual bool storeSimulationStep(jabs::simulation &simulation,unsigned currentStep) = 0;
    virtual bool storeSimulationParameter(const ParameterSimulation &parameter) = 0;
    virtual DataLogger* clone() const = 0;

};
}
#endif // DATALOGGER_H
