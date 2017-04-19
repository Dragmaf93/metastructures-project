#include "simulatorsmanager.h"

#include<QDebug>
FlockSimulator::SimulatorsManager::SimulatorsManager()
{
    mCurrentParallelThread=0;
    mSimulationStarted = false;
    mTotalSteps = 0;
    mCurrentTotalSteps = 0;
}

void FlockSimulator::SimulatorsManager::startSimulations()
{
    if(!mSimulationStarted){
        mMainThread = new QThread();
        mSimulationStarted = true;
        moveToThread(mMainThread);
        connect(mMainThread,SIGNAL(started()),this,SLOT(mainThreadRun()));
        connect(mMainThread, SIGNAL(finished()), mMainThread, SLOT(deleteLater()));
        mMainThread->start();
    }
}

void FlockSimulator::SimulatorsManager::reset()
{
    mParameterSimulations.clear();
    mTotalSteps = 0;
}

void FlockSimulator::SimulatorsManager::addSimulation(const FlockSimulator::ParameterSimulation &parameterSimulation)
{
    mParameterSimulations.enqueue(parameterSimulation);
    mTotalSteps+=parameterSimulation.getMaxStep();
}

void FlockSimulator::SimulatorsManager::addSimulations(const QQueue<ParameterSimulation> &pQueue)
{
    mParameterSimulations=pQueue;
}

void FlockSimulator::SimulatorsManager::setDataLogger(FlockSimulator::DataLogger *logger)
{
    mDataLogger = logger;
}

void FlockSimulator::SimulatorsManager::setMaxParallelThread(unsigned num)
{
    mMaxParallelThread = num;
}

unsigned FlockSimulator::SimulatorsManager::getNumParallelThread()
{
    return mMaxParallelThread;
}

unsigned FlockSimulator::SimulatorsManager::getProgress()
{
    mMutex.lock();
    int n = 0;
    QList<ThreadSimulator*> list = mActiveThreads.values();
    foreach (ThreadSimulator* t, list) {
        n += t->getProgress();
    }
    n+=mCurrentTotalSteps;
    mMutex.unlock();
    return n;
}

unsigned FlockSimulator::SimulatorsManager::getMaximumProgress()
{
    return mTotalSteps;
}

void FlockSimulator::SimulatorsManager::mainThreadRun()
{
    while(!mParameterSimulations.isEmpty()){
        ParameterSimulation p = mParameterSimulations.dequeue();


        mMutex.lock();

        while(mCurrentParallelThread >= mMaxParallelThread)
            mCondition.wait(&mMutex);
        mCurrentParallelThread++;


        mMutex.unlock();
        DataLogger* cln = mDataLogger->clone();
        ThreadSimulator * simulator = new ThreadSimulator(cln,this);

        if(simulator->initializeSimulation(p)){

            mActiveThreads.insert(simulator->id,simulator);

            connect(simulator, SIGNAL(finished()), simulator, SLOT(deleteLater()));
            connect(cln,SIGNAL(message(QString)),this,SLOT(sendMessage(QString)));
            connect(cln,SIGNAL(error(QString)),this,SLOT(sendError(QString)));

            emit message("Simulator_"+QString::number(simulator->id)+": Starts.");
            simulator->start();
        }else{

            emit error("Simulator_"+QString::number(simulator->id)+": Error during initilization of simulation.");

            delete simulator;
            mCurrentParallelThread--;
            mSimulationEnded++;
        }
    }
    mMutex.lock();

    while(mCurrentParallelThread > 0)
        mCondition.wait(&mMutex);

    mCurrentParallelThread++;

    mMutex.unlock();
    emit message("All simulations have finished.");

    emit end();
}

void FlockSimulator::SimulatorsManager::onFinished(int i)
{
    mMutex.lock();
    mCurrentParallelThread--;
    mCurrentTotalSteps += mActiveThreads[i]->getMaxStep();
    mActiveThreads.remove(i);
    mSimulationEnded++;
    emit message("Simulator_"+QString::number(i)+": Has finished.");
    if(mCurrentParallelThread<mMaxParallelThread)
        mCondition.wakeOne();
    mMutex.unlock();
}

void FlockSimulator::SimulatorsManager::simulatorEnd()
{
    //    emit end();
}
