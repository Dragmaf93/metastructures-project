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
    ThreadSimulator(DataLogger *logger, SimulatorsManager* manager);
    ~ThreadSimulator();

    bool initializeSimulation(const ParameterSimulation &parameterSimulation);
    void run();

    unsigned getProgress()const;
    unsigned getMaxStep()const;
    unsigned id;
private:
    unsigned mCurrentStep;

    unsigned mMaxStep;
    static  unsigned LAST_ID;

    jabs::simulation mSimulation;
    DataLogger* mDataLogger;

    SimulatorsManager* mManager;
signals:
    void simulationEnded();
};
}

#endif // THREADSIMULATOR_H
