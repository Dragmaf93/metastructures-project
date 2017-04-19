#ifndef SIMULATORSMANAGER_H
#define SIMULATORSMANAGER_H

#include"threadsimulator.h"

#include<QQueue>
#include<QMutex>
#include<QWaitCondition>
#include<QMap>
#include<QtConcurrent/QtConcurrent>
namespace FlockSimulator {

class ThreadSimulator;

class SimulatorsManager : public MessageSender{
    Q_OBJECT

friend class ProgressSignalEmiter;
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
    QThread* mProgressEmitter;

    bool mSimulationStarted;
    unsigned mMaxParallelThread;
    unsigned mCurrentParallelThread;

    QMutex mMutex;
    QWaitCondition mCondition;

    unsigned mTotalSimulations;
    unsigned mSimulationEnded;
    unsigned mTotalSteps;
    unsigned mCurrentTotalSteps;
    bool mSimEnd;
signals:
    void end();
    void progress(int);
public slots:
    void onFinished(int i);
    void emitProgressSignal();

private slots:
    void simulatorEnd();
    void mainThreadRun();
};

class ProgressSignalEmiter :public QThread{
public :
    SimulatorsManager* manager;
    void run();
};
}


#endif // SIMULATORSMANAGER_H
