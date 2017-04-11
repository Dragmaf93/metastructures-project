#ifndef THREADSIMULATOR_H
#define THREADSIMULATOR_H

#include "datalogger.h"

#include<QThread>
#include"SimulatorsManager.h"

namespace FlockSimulator {
class SimulatorsManager;

class ThreadSimulator : public QThread{
    Q_OBJECT

public:
    ThreadSimulator(const DataLogger *logger, SimulatorsManager* manager);
    ~ThreadSimulator();

    void initializeSimulation(const ParameterSimulation &parameterSimulation);
    void run();

    float getPercentage();
private:
    unsigned mCurrentStep;
    unsigned mMaxStep;

    jabs::simulation mSimulation;
    DataLogger* mDataLogger;

    SimulatorsManager* mManager;
signals:
    void simulationEnded();
};
}

#endif // THREADSIMULATOR_H
