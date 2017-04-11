#include "databaselogger.h"
FlockSimulator::DatabaseLogger::DatabaseLogger()
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
    const jabs::boid* b = &(simulation.getNation().getBoids()[0]);
    qDebug()<<currentStep<<b->pos.X <<b->pos.Y <<b->pos.Z;
}

bool FlockSimulator::DatabaseLogger::storeSimulationParameter(const ParameterSimulation &parameter)
{
    QSqlDatabase db = createConnection();
    if(db.open()){


        QSqlQuery query;
        query.prepare("insert into simulation(name,label,description) values(:name, :label, :description)");
        query.bindValue(":name",parameter.getSimulationName());
        query.bindValue(":label",parameter.getSimulationLabel());
        query.bindValue(":description",parameter.getSimulationDescription());
        if(!query.exec()) qDebug() << "ERRORE INSERT SIMULATION";

        db.close();
        return true;
    }else{
        db.close();
        return false;
    }
}

FlockSimulator::DataLogger *FlockSimulator::DatabaseLogger::clone() const
{
    return new DatabaseLogger(*this);
}

bool FlockSimulator::DatabaseLogger::testConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setPort(mDBPort);
    db.setHostName(mDBHost);
    db.setDatabaseName(mDBName);
    db.setUserName(mDBUser);
    db.setPassword(mDBPassword);
    if (!db.open())
    {
       db.close();
       qDebug() << db.lastError();
      return false;
    }

    return true;
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

QSqlDatabase & FlockSimulator::DatabaseLogger::createConnection()
{
    QSqlDatabase database = QSqlDatabase::addDatabase("QMYSQL");
    database.setPort(mDBPort);
    database.setHostName(mDBHost);
    database.setDatabaseName(mDBName);
    database.setUserName(mDBUser);
    database.setPassword(mDBPassword);
    return database;
}
