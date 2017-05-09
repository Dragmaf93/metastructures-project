#ifndef CSVDATALOGGER_H
#define CSVDATALOGGER_H

#include"DataLogger.h"

#include "qtcsv/stringdata.h"
#include "qtcsv/writer.h"

#include <QList>
#include <QStringList>
#include <QDir>
#include <QDebug>
#include <QTime>
#include <QFile>
namespace FlockSimulator{

class CsvDataLogger : public DataLogger{
    Q_OBJECT
public:
    CsvDataLogger();
    ~CsvDataLogger();
    CvsDataLogger(const CsvDataLogger& datalogger);


    virtual bool storeSimulationStep(jabs::simulation &simulation,unsigned currentStep);
    virtual bool storeSimulationParameter(const ParameterSimulation &parameter);
    virtual DataLogger* clone() const;

    void setDirectory(QString directory);
    QString getDirectory()const;

private:
    QString mDirectory;
    QString mParameters;

    QtCSV::StringData mDataStep;
    unsigned mMaxStep;

    void addParameter(QString name, QString value, bool endLine=true);
};
}

#endif // CSVDATALOGGER_H
