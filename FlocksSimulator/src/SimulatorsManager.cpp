#include "simulatorsmanager.h"

#include<QDebug>
FlockSimulator::SimulatorsManager::SimulatorsManager()
{
    mCurrentParallelThread=0;
    mSimulationStarted = false;
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
}

void FlockSimulator::SimulatorsManager::addSimulation(const FlockSimulator::ParameterSimulation &parameterSimulation)
{
    mParameterSimulations.enqueue(parameterSimulation);
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

float FlockSimulator::SimulatorsManager::getPercentage()
{

}

void FlockSimulator::SimulatorsManager::mainThreadRun()
{
    while(!mParameterSimulations.isEmpty()){
        ParameterSimulation p = mParameterSimulations.dequeue();

        ThreadSimulator * simulator = new ThreadSimulator(mDataLogger,this);
        mActiveThreads.append(simulator);
        simulator->initializeSimulation(p);
        connect(simulator, SIGNAL(finished()), simulator, SLOT(deleteLater()));

        mMutex.lock();

        while(mCurrentParallelThread >= mMaxParallelThread)
            mCondition.wait(&mMutex);
        mCurrentParallelThread++;

        mMutex.unlock();

        simulator->start();
    }
    mMutex.lock();

    while(mCurrentParallelThread > 0)
        mCondition.wait(&mMutex);

    mCurrentParallelThread++;

    mMutex.unlock();
    emit end();
}

void FlockSimulator::SimulatorsManager::onFinished()
{
    mMutex.lock();
    mCurrentParallelThread--;
    mSimulationEnded++;

    if(mCurrentParallelThread<mMaxParallelThread)
        mCondition.wakeOne();
    mMutex.unlock();
}

void FlockSimulator::SimulatorsManager::simulatorEnd()
{
//    emit end();
}
