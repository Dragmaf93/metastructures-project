#include "databaselogger.h"
unsigned FlockSimulator::DatabaseLogger::NUM_DB = 0;

FlockSimulator::DatabaseLogger::DatabaseLogger()
{
    QString name("ConnectionDB_");

    mConnectionName = name + QString::number(NUM_DB);
    QSqlDatabase::addDatabase("QMYSQL",mConnectionName);
    NUM_DB++;
}
FlockSimulator::DatabaseLogger::~DatabaseLogger()
{
    closeConnection();
    QSqlDatabase::removeDatabase(mConnectionName);
}

FlockSimulator::DatabaseLogger::DatabaseLogger(const FlockSimulator::DatabaseLogger &logger)
{
    mDBHost = logger.mDBHost;
    mDBName = logger.mDBName;
    mDBUser = logger.mDBUser;
    mDBPassword = logger.mDBPassword;
    mDBPort = logger.mDBPort;

    QString name("ConnectionDB_");
    mConnectionName = name + QString::number(NUM_DB);
    QSqlDatabase::addDatabase("QMYSQL",mConnectionName);
    NUM_DB++;

}

bool FlockSimulator::DatabaseLogger::storeSimulationStep(jabs::simulation &simulation, unsigned currentStep)
{
    QSqlDatabase database = QSqlDatabase::database(mConnectionName,false);
    if(connection()){

        for(unsigned boid = 0; boid < simulation.getNation().getBoids().size(); boid++){
            //            mSim << mLastIdSimulation;
            mStep << currentStep;
            mBoids << boid;
            mX << simulation.getNation().getBoids()[boid].pos.X;
            mY << simulation.getNation().getBoids()[boid].pos.Y;
            mZ << simulation.getNation().getBoids()[boid].pos.Z;
        }

        if(currentStep == mMaxStep -1){
            emit message(mConnectionName+": Storing data simulation.");

            QSqlQuery query(database);
            query.prepare("insert into microscopic_data(step , boid, positionX, positionY, positionZ,simulation) values"
                          "(?,?,?,?,?,?)");
            query.addBindValue(mStep);
            query.addBindValue(mBoids);
            query.addBindValue(mX);
            query.addBindValue(mY);
            query.addBindValue(mZ);

            QElapsedTimer timer;


            timer.start();

            database.transaction();

            if(mQuerySimulation->exec()){
                //                mQuerySimulation->lastError();
                mLastIdSimulation = mQuerySimulation->lastInsertId().toInt();
                //                qDebug() <<mLastIdSimulation;
                mQueryParameter->bindValue(":sim",mLastIdSimulation);

                for(unsigned s = 0; s < mBoids.size(); s++)
                    mSimStep << mLastIdSimulation;
                query.addBindValue(mSimStep);

                for(unsigned s = 0; s < mNumBoids.size(); s++)
                    mSimFlock << mLastIdSimulation;
                mQueryFlocks->addBindValue(mSimFlock);

                for(unsigned s = 0; s < mRadius.size(); s++)
                    mSimObstacle << mLastIdSimulation;

                if(!mQueryParameter->exec()){
                    emit error(mConnectionName+": "+mQueryParameter->lastError().text());
                }

                if(!mQueryFlocks->execBatch())
                    emit error(mConnectionName+": "+mQueryFlocks->lastError().text());

                if(mSimObstacle.size() > 0){
                    mQueryObstacles->addBindValue(mSimObstacle);
                    if(!mQueryObstacles->execBatch())
                        emit error(mConnectionName+": "+mQueryObstacles->lastError().text());
                }

                if(!query.execBatch()){
                    emit error(mConnectionName+": "+query.lastError().text());
                    delete mQueryParameter;
                    delete mQuerySimulation;
                    database.rollback();
                    return false;
                }
                if(!database.commit()){
                    emit error(mConnectionName+": "+database.lastError().text());
                    delete mQueryParameter;
                    delete mQuerySimulation;
                    database.rollback();
                    return false;
                }
                //                qDebug()<<mConnectionName<<": Data have been stored in "<<QString::number(timer.elapsed())<<" milliseconds";
                emit message(mConnectionName+": Data have been stored in "+QString::number(timer.elapsed())+" milliseconds.");
                delete mQueryParameter;
                delete mQuerySimulation;
                return true;
            }else {
                database.rollback();
                delete mQueryParameter;
                delete mQuerySimulation;

                emit error(mConnectionName+": "+database.lastError().text());
                return false;
            }
        }
    }else{
        delete mQueryParameter;
        delete mQuerySimulation;

        qDebug() << mConnectionName+": "+database.lastError().text();
        emit error(mConnectionName+": "+database.lastError().text());
        return false;
    }
}

bool FlockSimulator::DatabaseLogger::storeSimulationParameter(const ParameterSimulation &parameter)
{
    QSqlDatabase database = QSqlDatabase::database(mConnectionName,false);

    if(connection()){
        mQuerySimulation = new QSqlQuery(database);

        mQuerySimulation->prepare("insert into simulation(name,label,description) values(:name, :label, :description)");
        mQuerySimulation->bindValue(":name",parameter.getSimulationName());
        mQuerySimulation->bindValue(":label",parameter.getSimulationLabel());
        mQuerySimulation->bindValue(":description",parameter.getSimulationDescription());
        //        if(!mQuerySimulation.->exec()) qDebug() <<mQuerySimulation.lastError();

        //        mLastIdSimulation = mQuerySimulation->lastInsertId().toInt();
        float timeStepSec = float(parameter.getTimeStep())/ 1000;
        mMaxStep = unsigned ((float)parameter.getTimeLimit()/timeStepSec);

        mQueryParameter = new QSqlQuery(database);
        mQueryParameter->prepare("insert into simulation_parameter(simulation, force_space, radius_space, time_limit, time_step, predation, seed)"
                                 " values (:sim, :fs, :rs, :tl, :ts, :p, :seed)");
        //        mQueryParameter->bindValue(":sim",mLastIdSimulation);
        mQueryParameter->bindValue(":fs",parameter.getForceSpace());
        mQueryParameter->bindValue(":rs",parameter.getRadiusSpace());
        mQueryParameter->bindValue(":tl",parameter.getTimeLimit());
        mQueryParameter->bindValue(":ts",parameter.getTimeStep());
        mQueryParameter->bindValue(":p",parameter.isPredationEnabled());
        mQueryParameter->bindValue(":seed",parameter.getRandomSeed());

        mQueryFlocks = new QSqlQuery(database);
        mQueryFlocks->prepare("insert into init_flock(boids_number,"
                              "specie, min_x, max_x, min_z, max_z, simulation) values (?,?,?,?,?,?,?)");

        QVector<FlockSimulator::ParameterSimulation::Flock> flocks = parameter.getFlocks();
        foreach (FlockSimulator::ParameterSimulation::Flock flock, flocks) {
            mNumBoids << flock.numBoids;
            mMinX <<flock.xMin;
            mMaxX <<flock.xMax;
            mMinZ <<flock.zMin;
            mMaxZ <<flock.zMax;
            mSpecie <<flock.specie;
        }
        mQueryFlocks->addBindValue(mNumBoids);
        mQueryFlocks->addBindValue(mSpecie);
        mQueryFlocks->addBindValue(mMinX);
        mQueryFlocks->addBindValue(mMaxX);
        mQueryFlocks->addBindValue(mMinZ);
        mQueryFlocks->addBindValue(mMaxZ);

        if(!parameter.getObstacles().isEmpty()){
            qDebug() <<"Ciao";
            mQueryObstacles = new QSqlQuery(database);
            mQueryObstacles->prepare("insert into init_obstacle(radius,x,y,z,simulation) values(?,?,?,?,?)");

            QVector<FlockSimulator::ParameterSimulation::Obstacle> obstacles = parameter.getObstacles();
            foreach (FlockSimulator::ParameterSimulation::Obstacle obstacle, obstacles) {
                mRadius << obstacle.radius;
                mCenterX <<obstacle.x;
                mCenterY <<obstacle.y;
                mCenterZ <<obstacle.z;
            }
            mQueryObstacles->addBindValue(mRadius);
            mQueryObstacles->addBindValue(mCenterX);
            mQueryObstacles->addBindValue(mCenterY);
            mQueryObstacles->addBindValue(mCenterZ);
        }

        return true;

    }else{
        delete mQueryParameter;
        delete mQuerySimulation;
        qDebug() << mConnectionName+": "+database.lastError().text();
        emit error(mConnectionName+": "+database.lastError().text());
        return false;
    }
}

FlockSimulator::DataLogger *FlockSimulator::DatabaseLogger::clone() const
{
    return new DatabaseLogger(*this);
}

bool FlockSimulator::DatabaseLogger::testConnection()
{
    return connection();
}

void FlockSimulator::DatabaseLogger::closeConnection()
{
    QSqlDatabase database = QSqlDatabase::database(mConnectionName,false);

    if(database.isOpen())
        database.close();
}

void FlockSimulator::DatabaseLogger::setDatabaseName(QString name)
{
    mDBName = name;
}

void FlockSimulator::DatabaseLogger::setDatabasePassword(QString password)
{
    mDBPassword = password;
}

void FlockSimulator::DatabaseLogger::setDatabaseUser(QString user)
{
    mDBUser = user;
}

void FlockSimulator::DatabaseLogger::setDatabaseHost(QString host)
{
    mDBHost = host;
}

void FlockSimulator::DatabaseLogger::setDatabasePort(unsigned port)
{
    mDBPort = port;
}

QString FlockSimulator::DatabaseLogger::getDatabaseName() const
{
    return mDBName;
}

QString FlockSimulator::DatabaseLogger::getDatabasePassword() const
{
    return mDBPassword;
}

QString FlockSimulator::DatabaseLogger::getDatabaseUser() const
{
    return mDBUser;
}

QString FlockSimulator::DatabaseLogger::getDatabaseHost() const
{
    return mDBHost;
}

unsigned FlockSimulator::DatabaseLogger::getDatabasePort() const
{
    return mDBPort;
}

bool FlockSimulator::DatabaseLogger::connection()
{
    QSqlDatabase database = QSqlDatabase::database(mConnectionName,false);
    if(!database.isValid()){
        emit error(mConnectionName+": "+database.lastError().text());
        return false;
    }
    if(!database.isOpen()){
        database.setPort(mDBPort);
        database.setHostName(mDBHost);
        database.setDatabaseName(mDBName);
        database.setUserName(mDBUser);
        database.setPassword(mDBPassword);
        return database.open();
    }
    return true;
}
