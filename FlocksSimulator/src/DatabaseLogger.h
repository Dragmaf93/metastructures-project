#ifndef DATABASELOGGER_H
#define DATABASELOGGER_H

#include<QtSql>
#include"DataLogger.h"
#include<QDebug>
#include<QThread>
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
    static QSqlDatabase DATABASE;
    QString mDBName;
    QString mDBPassword;
    QString mDBUser;
    QString mDBHost;
    unsigned mDBPort;
    int mLastIdSimulation;
    bool connection();
    QVariantList mSim;
    QVariantList mStep;
    QVariantList mBoids;
    QVariantList mX;
    QVariantList mY;
    QVariantList mZ;
    unsigned mMaxStep;
private slots:
};
}
#endif // DATABASELOGGER_H
