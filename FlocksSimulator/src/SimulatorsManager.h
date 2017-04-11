#ifndef SIMULATORSMANAGER_H
#define SIMULATORSMANAGER_H

#include"threadsimulator.h"

#include<QQueue>
#include<QMutex>
#include<QWaitCondition>

namespace FlockSimulator {
class ThreadSimulator;
class SimulatorsManager : public QObject{
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

    float getPercentage();
private:
    DataLogger* mDataLogger;

    QQueue<ParameterSimulation> mParameterSimulations;
    QList<ThreadSimulator*> mActiveThreads;

    QThread* mMainThread;

    bool mSimulationStarted;
    unsigned mMaxParallelThread;
    unsigned mCurrentParallelThread;

    QMutex mMutex;
    QWaitCondition mCondition;

    unsigned mTotalSimulations;
    unsigned mSimulationEnded;
signals:
    void end();

public slots:
    void onFinished();
private slots:
    void simulatorEnd();
    void mainThreadRun();
};
}

#endif // SIMULATORSMANAGER_H
