#ifndef PARAMETERSIMULATION_H
#define PARAMETERSIMULATION_H

#include<QVector>

namespace FlockSimulator{

#define DEFAULT_TIME_LIMIT_SEC 30
#define DEFAULT_TIME_STEP_MSEC 30
#define DEFAULT_PREDATION_ENABLED 0
#define DEFAULT_RANDOM_SEED 0
#define DEFAULT_RADIUS_OR 20.00
#define DEFAULT_FORCE_OR 18.00
#define DEFAULT_OBSTACLE_RADIUS 5.00
#define DEFAULT_OBSTACLE_X 10.00
#define DEFAULT_OBSTACLE_Y 10.00
#define DEFAULT_OBSTACLE_Z 10.00
#define DEFAULT_NUM_BOID 50
#define DEFAULT_SPECIE 0
#define DEFAULT_FLOCK_XMIN -20.00
#define DEFAULT_FLOCK_XMAX -5.00
#define DEFAULT_FLOCK_ZMIN -20.00
#define DEFAULT_FLOCK_ZMAX -5.00

class ParameterSimulation
{
public:
    struct Flock{

        Flock(unsigned n=DEFAULT_NUM_BOID,float xMn=DEFAULT_FLOCK_XMIN,float xMx=DEFAULT_FLOCK_XMAX,
              float zMn=DEFAULT_FLOCK_ZMIN,float zMx=DEFAULT_FLOCK_ZMAX,unsigned s=DEFAULT_SPECIE)
            :numBoids(n),xMin(xMn),xMax(xMx),
              zMin(zMn),zMax(zMx),specie(s){}

        unsigned numBoids;
        float xMin;
        float xMax;
        float zMin;
        float zMax;
        unsigned specie;

    };

    struct Obstacle{
        Obstacle(float X=DEFAULT_OBSTACLE_X,float Y=DEFAULT_OBSTACLE_Y,
                 float Z=DEFAULT_OBSTACLE_Z,float r=DEFAULT_OBSTACLE_RADIUS):
            x(X),y(Y),z(Z),radius(r){}

        float x, y, z;
        float radius;
    };

    ParameterSimulation();

    void setTimeLimit(unsigned timeSec);
    void setTimeStep(unsigned timeMilliSec);

    void setRadiusSpace(float radiusSpace);
    void setForceSpace(float forceSpece);

    void setRandomSeed(unsigned seed);

    unsigned getTimeLimit()const;
    unsigned getTimeStep()const;

    float getRadiusSpace()const;
    float getForceSpace()const;

    unsigned getRandomSeed()const;

    void setPredation(bool);
    bool isPredationEnabled()const;

    void addFlock(const Flock &flock);
    void addObstacle(const Obstacle &obstacle);

    void setFlocks(QVector <Flock> &flocks);
    void setObstacles(QVector <Obstacle> &obstacle);

    QVector<Flock> getFlocks()const;
    QVector<Obstacle> getObstacles()const;

    void setSimulationLabel(QString label);
    void setSimulationName(QString name);
    void setSimulationDescription(QString description);

    QString getSimulationLabel()const;
    QString getSimulationName()const;
    QString getSimulationDescription()const;

private:

    QString mSimulationLabel;
    QString mSimulationName;
    QString mSimulationDescription;

    unsigned mTimeLimitSec;
    unsigned mTimeStepMilliSec;

    bool mPredationEnabled;

    float mRadiusSpace;
    float mForceSpace;

    unsigned mRandomSeed;

    QVector<Flock> mFlocksVector;
    QVector<Obstacle> mObstaclesVector;
};

}
#endif // PARAMETERSIMULATION_H
