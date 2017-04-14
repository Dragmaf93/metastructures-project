#include "databaselogger.h"
FlockSimulator::DatabaseLogger::DatabaseLogger()
{

}

FlockSimulator::DatabaseLogger::~DatabaseLogger()
{

}

FlockSimulator::DatabaseLogger::DatabaseLogger(const FlockSimulator::DatabaseLogger &logger)
{
    mDBHost = logger.mDBHost;
    mDBName = logger.mDBName;
    mDBUser = logger.mDBUser;
    mDBPassword = logger.mDBPassword;
}

bool FlockSimulator::DatabaseLogger::storeSimulationStep(jabs::simulation &simulation, unsigned currentStep)
{
    if(connection()){

        QSqlQuery query;
        query.prepare("insert into microscopic_data(simulation, step , boid, positionX, positionY, positionZ) values"
                      "(?,?,?,?,?,?)");
        //        "(:sim, :step, :boid, :x, :y, :z)");

        const jabs::boid* b = &(simulation.getNation().getBoids()[0]);
        for(unsigned boid = 0; boid < simulation.getNation().getBoids().size(); boid++){
            mSim << mLastIdSimulation;
            mStep << currentStep;
            mBoids << boid;
            mX << simulation.getNation().getBoids()[boid].pos.X;
            mY << simulation.getNation().getBoids()[boid].pos.Y;
            mZ << simulation.getNation().getBoids()[boid].pos.Z;
        }
        if(currentStep == mMaxStep -1){
            qDebug() << "PREPARAZIONE";
            query.addBindValue(mSim);
            query.addBindValue(mStep);
            query.addBindValue(mBoids);
            query.addBindValue(mX);
            query.addBindValue(mY);
            query.addBindValue(mZ);
            QElapsedTimer timer;


            timer.start();
            qDebug() << "INIZIO";
            DATABASE.transaction();
            if(!query.execBatch())
                qDebug()<<query.lastError();
            qDebug() << "FINE"<<timer.elapsed();
            DATABASE.commit();
//            QThread* thread = new QThread();
//            moveToThread(thread);
//            connect(thread,SIGNAL(started()),this,SLOT(insertToDatabase()));
//            connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
//            thread->start();
        }
    }
}

bool FlockSimulator::DatabaseLogger::storeSimulationParameter(const ParameterSimulation &parameter)
{
    qDebug() << "CIAOOO";
    if(connection()){
        QSqlQuery querySimulation;

        querySimulation.prepare("insert into simulation(name,label,description) values(:name, :label, :description)");
        querySimulation.bindValue(":name",parameter.getSimulationName());
        querySimulation.bindValue(":label",parameter.getSimulationLabel());
        querySimulation.bindValue(":description",parameter.getSimulationDescription());
        if(!querySimulation.exec()) qDebug() << "ERRORE INSERT SIMULATION";

        mLastIdSimulation = querySimulation.lastInsertId().toInt();
        float timeStepSec = float(parameter.getTimeStep())/ 1000;
        mMaxStep = unsigned ((float)parameter.getTimeLimit()/timeStepSec);

        QSqlQuery queryParameter;
        queryParameter.prepare("insert into simulation_parameter(simulation, force_space, radius_space, time_limit, time_step, predation, seed)"
                               " values (:sim, :fs, :rs, :tl, :ts, :p, :seed)");
        queryParameter.bindValue(":sim",mLastIdSimulation);
        queryParameter.bindValue(":fs",parameter.getForceSpace());
        queryParameter.bindValue(":rs",parameter.getRadiusSpace());
        queryParameter.bindValue(":tl",parameter.getTimeLimit());
        queryParameter.bindValue(":ts",parameter.getTimeStep());
        queryParameter.bindValue(":p",parameter.isPredationEnabled());
        queryParameter.bindValue(":seed",parameter.getRandomSeed());

        if(!queryParameter.exec()) qDebug() <<queryParameter.lastError();

        return true;
    }else{
        return false;
    }
}

FlockSimulator::DataLogger *FlockSimulator::DatabaseLogger::clone() const
{
    return new DatabaseLogger(*this);
}

bool FlockSimulator::DatabaseLogger::testConnection()
{
    //    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    //    db.setPort(mDBPort);
    //    db.setHostName(mDBHost);
    //    db.setDatabaseName(mDBName);
    //    db.setUserName(mDBUser);
    //    db.setPassword(mDBPassword);
    //    if (!db.open())
    //    {
    //       db.close();
    //       qDebug() << db.lastError();
    //      return false;
    //    }
    //    db.close();
    return connection();
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
QSqlDatabase FlockSimulator::DatabaseLogger::DATABASE= QSqlDatabase::addDatabase("QMYSQL");

bool FlockSimulator::DatabaseLogger::connection()
{

    if(!DATABASE.isOpen()){

        DATABASE.setPort(mDBPort);
        DATABASE.setHostName(mDBHost);
        DATABASE.setDatabaseName(mDBName);
        DATABASE.setUserName(mDBUser);
        DATABASE.setPassword(mDBPassword);

        return DATABASE.open();
    }
    return true;
}
