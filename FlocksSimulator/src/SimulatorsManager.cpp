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


        mMutex.lock();

        while(mCurrentParallelThread >= mMaxParallelThread)
            mCondition.wait(&mMutex);
        mCurrentParallelThread++;

        mMutex.unlock();

        DataLogger* cln = mDataLogger->clone();
        ThreadSimulator * simulator = new ThreadSimulator(cln,this);

        if(simulator->initializeSimulation(p)){

            mActiveThreads.append(simulator);
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
