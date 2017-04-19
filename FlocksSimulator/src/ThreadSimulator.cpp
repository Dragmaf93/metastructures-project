#include "threadsimulator.h"
#include<QDebug>
unsigned FlockSimulator::ThreadSimulator::LAST_ID = 0;
FlockSimulator::ThreadSimulator::ThreadSimulator(FlockSimulator::DataLogger *logger, SimulatorsManager* manager)
{
    mManager =manager;
    mDataLogger = logger;
    id = LAST_ID++;
}

FlockSimulator::ThreadSimulator::~ThreadSimulator()
{
    delete mDataLogger;
}

bool FlockSimulator::ThreadSimulator::initializeSimulation(const FlockSimulator::ParameterSimulation &p)
{
    if(!mDataLogger->storeSimulationParameter(p)) return false;

    jabs::boidNation::flockInitSetup    flockSetup;
    jabs::boidNation::flockInitSetupList flockSetupList;

    float timeStepSec = float(p.getTimeStep())/ 1000;
    mMaxStep = unsigned ((float)p.getTimeLimit()/timeStepSec);
    mCurrentStep = 0;

    mSimulation.setTimeStep(timeStepSec);

    mSimulation.setRadiusOr(p.getRadiusSpace());
    mSimulation.setForceOr(p.getForceSpace());

    flockSetup.posDist.coordSystem = jabs::csCartesian;
    flockSetup.posDist.coordSetups[0].probDist = jabs::pdUniform;
    flockSetup.posDist.coordSetups[1].probDist = jabs::pdUniform;
    flockSetup.posDist.coordSetups[1].firstParam = 0.0;
    flockSetup.posDist.coordSetups[1].secondParam = 0.0;
    flockSetup.posDist.coordSetups[2].probDist = jabs::pdUniform;

    unsigned c = 0, randomSeed = p.getRandomSeed();

    QVector<ParameterSimulation::Flock> flocksVector = p.getFlocks();

    for (unsigned i = 0; i  < flocksVector.size(); i++) {

        flockSetup.species = flocksVector[i].specie ;
        flockSetup.numBoids = flocksVector[i].numBoids;
        flockSetup.posDist.coordSetups[0].firstParam = flocksVector[i].xMin;
        flockSetup.posDist.coordSetups[0].secondParam =flocksVector[i].xMax;
        flockSetup.posDist.coordSetups[0].seed = randomSeed + i + c++;
        flockSetup.posDist.coordSetups[1].seed = randomSeed + i + c++;
        flockSetup.posDist.coordSetups[2].firstParam =flocksVector[i].zMin;
        flockSetup.posDist.coordSetups[2].secondParam = flocksVector[i].zMax;
        flockSetup.posDist.coordSetups[2].seed = randomSeed + i + c;

        if (p.isPredationEnabled())
            mSimulation.setPredationGroup(flockSetup.species, flockSetup.species);
        else
            mSimulation.setPredationGroup(flockSetup.species, 0);

        flockSetupList.push_back(flockSetup);
    }

    mSimulation.initFlocks(flockSetupList);

    QVector<ParameterSimulation::Obstacle> obstaclesVector = p.getObstacles();

    foreach (ParameterSimulation::Obstacle o, obstaclesVector) {

        jabs::sphere s;
        s.center.X = o.x;
        s.center.Y = o.y;
        s.center.Z = o.z;
        s.radius = o.radius;

        mSimulation.addSphereObstacle(s);
    }
    return true;
}

void FlockSimulator::ThreadSimulator::run()
{
    mCurrentStep = 0;
    while(mCurrentStep < mMaxStep){

        mSimulation.run();
//        if(mCurrentStep%100 ==0) /*qDebug*/() <<id<< "  "<<mCurrentStep;
        mDataLogger->storeSimulationStep(mSimulation,mCurrentStep);
        mCurrentStep++;
    }
    mManager->onFinished(id);
    emit simulationEnded();
}

float FlockSimulator::ThreadSimulator::getPercentage(){
    return (100.0f * (float)mCurrentStep)/(float)mMaxStep;
}
