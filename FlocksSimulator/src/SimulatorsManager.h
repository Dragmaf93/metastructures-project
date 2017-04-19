#ifndef SIMULATORSMANAGER_H
#define SIMULATORSMANAGER_H

#include"threadsimulator.h"

#include<QQueue>
#include<QMutex>
#include<QWaitCondition>
#include<QMap>
namespace FlockSimulator {

class ThreadSimulator;

class SimulatorsManager : public MessageSender{
    Q_OBJECT

public:
    SimulatorsManager();

    void startSimulations();
    void reset();

    void addSimulation(const ParameterSimulation &parameterSimulation);
    void addSimulations(const QQueue<ParameterSimulation> &pQueue);

    void setDataLogger(DataLogger* logger);

    void setMaxParallelThread(unsigned num);
    unsigned getNumParallelThread();

    unsigned getProgress();
    unsigned getMaximumProgress();
private:
    DataLogger* mDataLogger;

    QQueue<ParameterSimulation> mParameterSimulations;
    QMap<int, ThreadSimulator*> mActiveThreads;

    QThread* mMainThread;

    bool mSimulationStarted;
    unsigned mMaxParallelThread;
    unsigned mCurrentParallelThread;

    QMutex mMutex;
    QWaitCondition mCondition;

    unsigned mTotalSimulations;
    unsigned mSimulationEnded;
    unsigned mTotalSteps;
    unsigned mCurrentTotalSteps;
signals:
    void end();

public slots:
    void onFinished(int i);

private slots:
    void simulatorEnd();
    void mainThreadRun();
};
}

#endif // SIMULATORSMANAGER_H
