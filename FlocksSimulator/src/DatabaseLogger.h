#ifndef DATABASELOGGER_H
#define DATABASELOGGER_H

#include<QtSql>
#include"DataLogger.h"
#include<QDebug>
namespace FlockSimulator {

class DatabaseLogger: public DataLogger{

public:

    DatabaseLogger();
    DatabaseLogger(const DatabaseLogger &logger);

    virtual bool storeSimulationStep(jabs::simulation &simulation, unsigned currentStep);
    virtual bool storeSimulationParameter(const ParameterSimulation &parameter);
    virtual DataLogger *clone()const;

    bool testConnection();

    void setDatabaseName(QString name);
    void setDatabasePassword(QString password);
    void setDatabaseUser(QString user);
    void setDatabaseHost(QString host);
    void setDatabasePort(unsigned port);

    QString getDatabaseName()const;
    QString getDatabasePassword()const;
    QString getDatabaseUser()const;
    QString getDatabaseHost()const;
    unsigned getDatabasePort()const;

private:

    QString mDBName;
    QString mDBPassword;
    QString mDBUser;
    QString mDBHost;
    unsigned mDBPort;

    QSqlDatabase& createConnection();

};
}
#endif // DATABASELOGGER_H
