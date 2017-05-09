#include "parametersimulation.h"

FlockSimulator::ParameterSimulation::ParameterSimulation()
{
   mTimeLimitSec = DEFAULT_TIME_LIMIT_SEC;
   mTimeStepMilliSec = DEFAULT_TIME_STEP_MSEC;
   mRadiusSpace = DEFAULT_RADIUS_OR;
   mRandomSeed = DEFAULT_RANDOM_SEED;
   mForceSpace = DEFAULT_FORCE_OR;
   mPredationEnabled = DEFAULT_PREDATION_ENABLED;
   mCollisionAvoidance = DEFAULT_CA;
   mForceFlockCentering = DEFAULT_FORCE_FC;
   mVelocityAllignment = DEFAULT_VA;
   mFlocksVector.append(Flock());
}

void FlockSimulator::ParameterSimulation::setTimeLimit(unsigned timeSec)
{
    mTimeLimitSec = timeSec;
}

void FlockSimulator::ParameterSimulation::setTimeStep(unsigned timeMilliSec)
{
    mTimeStepMilliSec = timeMilliSec;
}

void FlockSimulator::ParameterSimulation::setRadiusSpace(float radiusSpace)
{
    mRadiusSpace = radiusSpace;
}

void FlockSimulator::ParameterSimulation::setForceSpace(float forceSpace)
{
    mForceSpace = forceSpace;
}

void FlockSimulator::ParameterSimulation::setCollissionAvoidance(float collisionA)
{
    mCollisionAvoidance = collisionA;
}

void FlockSimulator::ParameterSimulation::setForceFlockCentering(float flockCentering)
{
    mForceFlockCentering = flockCentering;
}

void FlockSimulator::ParameterSimulation::setVelocityAllignemt(float velAll)
{
    mVelocityAllignment = velAll;
}

void FlockSimulator::ParameterSimulation::setRandomSeed(unsigned seed)
{
    mRandomSeed = seed;
}

unsigned FlockSimulator::ParameterSimulation::getTimeLimit() const
{
    return mTimeLimitSec;
}

unsigned FlockSimulator::ParameterSimulation::getTimeStep() const
{
    return mTimeStepMilliSec;
}

float FlockSimulator::ParameterSimulation::getRadiusSpace() const
{
    return mRadiusSpace;
}

float FlockSimulator::ParameterSimulation::getForceSpace() const
{
    return mForceSpace;
}

float FlockSimulator::ParameterSimulation::getCollissionAvoidance() const
{
    return mCollisionAvoidance;
}

float FlockSimulator::ParameterSimulation::getForceFlockCentering() const
{
    return mForceFlockCentering;
}

float FlockSimulator::ParameterSimulation::getVelocityAlignemt() const
{
    return mVelocityAllignment;
}

unsigned FlockSimulator::ParameterSimulation::getRandomSeed() const
{
    return mRandomSeed;
}

void FlockSimulator::ParameterSimulation::setPredation(bool b)
{
    mPredationEnabled = b;
}

bool FlockSimulator::ParameterSimulation::isPredationEnabled()const
{
    return mPredationEnabled;
}

void FlockSimulator::ParameterSimulation::addFlock(const FlockSimulator::ParameterSimulation::Flock &flock)
{
    mFlocksVector.push_back(flock);
}

void FlockSimulator::ParameterSimulation::addObstacle(const FlockSimulator::ParameterSimulation::Obstacle &obstacle)
{
    mObstaclesVector.push_back(obstacle);
}

void FlockSimulator::ParameterSimulation::setFlocks(QVector<FlockSimulator::ParameterSimulation::Flock> &flocks)
{
    mFlocksVector.clear();
    mFlocksVector = flocks;
}

void FlockSimulator::ParameterSimulation::setObstacles(QVector<FlockSimulator::ParameterSimulation::Obstacle> &obstacles)
{
    mObstaclesVector.clear();
    mObstaclesVector = obstacles;
}

QVector<FlockSimulator::ParameterSimulation::Flock> FlockSimulator::ParameterSimulation::getFlocks() const
{
    return mFlocksVector;
}

QVector<FlockSimulator::ParameterSimulation::Obstacle> FlockSimulator::ParameterSimulation::getObstacles() const
{
    return mObstaclesVector;
}

void FlockSimulator::ParameterSimulation::clearFlocks()
{
    mFlocksVector.clear();
}

void FlockSimulator::ParameterSimulation::clearObstacles()
{
    mObstaclesVector.clear();
}

void FlockSimulator::ParameterSimulation::setSimulationLabel(QString label)
{
    mSimulationLabel = label;
}

void FlockSimulator::ParameterSimulation::setSimulationName(QString name)
{
    mSimulationName = name;
}

void FlockSimulator::ParameterSimulation::setSimulationDescription(QString description)
{
    mSimulationDescription = description;
}

QString FlockSimulator::ParameterSimulation::getSimulationLabel() const
{
    return mSimulationLabel;
}

QString FlockSimulator::ParameterSimulation::getSimulationName() const
{
    return mSimulationName;

}

QString FlockSimulator::ParameterSimulation::getSimulationDescription() const
{
    return mSimulationDescription;
}

unsigned FlockSimulator::ParameterSimulation::getMaxStep() const
{
    float timeStepSec = float(mTimeStepMilliSec)/ 1000;
    return unsigned ((float)mTimeLimitSec/timeStepSec);

}
