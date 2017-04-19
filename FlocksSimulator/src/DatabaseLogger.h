#ifndef DATABASELOGGER_H
#define DATABASELOGGER_H

#include<QtSql>
#include<QDebug>
#include<QThread>

#include"DataLogger.h"

namespace FlockSimulator {

class DatabaseLogger: public DataLogger{
 Q_OBJECT
public:

    DatabaseLogger();
    ~DatabaseLogger();
    DatabaseLogger(const DatabaseLogger &logger);

    virtual bool storeSimulationStep(jabs::simulation &simulation, unsigned currentStep);
    virtual bool storeSimulationParameter(const ParameterSimulation &parameter);
    virtual DataLogger *clone()const;

    bool testConnection();
    void closeConnection();

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
    static unsigned NUM_DB;
//    QSqlDatabase mDatabase;
    QSqlQuery* mQuerySimulation;
    QSqlQuery* mQueryParameter;

    QString mConnectionName;

    QString mDBName;
    QString mDBPassword;
    QString mDBUser;
    QString mDBHost;
    unsigned mDBPort;

    unsigned mMaxStep;
    int mLastIdSimulation;
    bool connection();

    QVariantList mSim;
    QVariantList mStep;
    QVariantList mBoids;
    QVariantList mX;
    QVariantList mY;
    QVariantList mZ;


private slots:
};
}
#endif // DATABASELOGGER_H
