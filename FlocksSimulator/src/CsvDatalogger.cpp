#include "CsvDatalogger.h"

FlockSimulator::CsvDataLogger::CsvDataLogger()
{
    mMaxStep=0;
    mDirectory="";
}

FlockSimulator::CsvDataLogger::~CsvDataLogger()
{

}

FlockSimulator::CsvDataLogger::CvsDataLogger(const FlockSimulator::CsvDataLogger &datalogger)
{
    mDirectory = datalogger.mDirectory;
    mMaxStep = 0;
}

bool FlockSimulator::CsvDataLogger::storeSimulationStep(jabs::simulation &simulation, unsigned currentStep)
{

    QStringList csvRow;

    for(unsigned boid = 0; boid < simulation.getNation().getBoids().size(); boid++){

        csvRow.clear();

        csvRow << QString::number(currentStep);
        csvRow << QString::number(boid);
        csvRow << QString::number(simulation.getNation().getBoids()[boid].pos.X);
        csvRow << QString::number(simulation.getNation().getBoids()[boid].pos.Y);
        csvRow << QString::number(simulation.getNation().getBoids()[boid].pos.Z);
        csvRow << QString::number(simulation.getNation().getBoids()[boid].vel.X);
        csvRow << QString::number(simulation.getNation().getBoids()[boid].vel.Y);
        csvRow << QString::number(simulation.getNation().getBoids()[boid].vel.Z);
        mDataStep.addRow(csvRow);

        //            mSim << mLastIdSimulation;
    }

    if(currentStep == mMaxStep - 1 ){

        QString dirPath = mDirectory+"/Sim_"+QDateTime::currentDateTime().toString("ddMMMMyyyy_hh.mm.ss.z");

        QString filePath = dirPath + "/data.csv";

        QDir().mkdir(dirPath);

        QFile file(dirPath+"/parameter.txt");

        if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
            return false;

        qDebug()<< "Ciao";

        QTextStream stream(&file);
        stream << mParameters;
        return QtCSV::Writer::write(filePath, mDataStep,";");
    }
    return true;
}

bool FlockSimulator::CsvDataLogger::storeSimulationParameter(const FlockSimulator::ParameterSimulation &parameter)
{

    mMaxStep = parameter.getMaxStep();

    addParameter("Name",parameter.getSimulationName());
    addParameter("Label",parameter.getSimulationLabel());
    addParameter("Descritpion",parameter.getSimulationDescription());
    addParameter("Force space",QString::number(parameter.getForceSpace()));
    addParameter("Radius space",QString::number(parameter.getForceSpace()));
    addParameter("Force flock centering",QString::number(parameter.getForceFlockCentering()));
    addParameter("Velocity alignment",QString::number(parameter.getVelocityAlignemt()));
    addParameter("Collision avoidance",QString::number(parameter.getCollissionAvoidance()));
    addParameter("Time limit",QString::number(parameter.getTimeLimit()));
    addParameter("Time step",QString::number(parameter.getTimeStep()));
    addParameter("Seed",QString::number(parameter.getRandomSeed()));
    addParameter("Predation",QString::number(parameter.isPredationEnabled()));
    addParameter("Flocks",".");

    QVector<FlockSimulator::ParameterSimulation::Flock> flocks = parameter.getFlocks();
    foreach (FlockSimulator::ParameterSimulation::Flock flock, flocks) {
        addParameter("\tBoids number",QString::number(flock.numBoids),false);
        addParameter("Specie",QString::number(flock.specie),false);
        addParameter("Min x",QString::number(flock.xMin),false);
        addParameter("Max x",QString::number(flock.xMax),false);
        addParameter("Min z",QString::number(flock.zMin),false);
        addParameter("Max z",QString::number(flock.zMax),true);
    }

    addParameter("Obstacles",".");
    QVector<FlockSimulator::ParameterSimulation::Obstacle> obstacles = parameter.getObstacles();
    foreach (FlockSimulator::ParameterSimulation::Obstacle obstacle, obstacles) {
        addParameter("\tRadius",QString::number(obstacle.radius),false);
        addParameter("Center x",QString::number(obstacle.x),false);
        addParameter("Center y",QString::number(obstacle.y),false);
        addParameter("Center z",QString::number(obstacle.z),true);
    }

    QStringList csvRow;
    csvRow << "step" << "boid" << "posX" << "posY" << "posZ" << "speedX" << "speedY" << "speedZ";
    mDataStep.addRow(csvRow);
    return true;
}

FlockSimulator::DataLogger *FlockSimulator::CsvDataLogger::clone() const
{
    CsvDataLogger* logger = new CsvDataLogger();
    logger->mMaxStep = 0;
    logger->mDirectory = mDirectory;

    return logger;
}

void FlockSimulator::CsvDataLogger::setDirectory(QString directory)
{
    mDirectory = directory;
}

QString FlockSimulator::CsvDataLogger::getDirectory() const
{
    return mDirectory;
}

void FlockSimulator::CsvDataLogger::addParameter(QString name, QString value, bool endLine)
{
    if(value.isEmpty()) value="NULL VALUE";

    if(value == "."){
        mParameters += name+"\n";
        return;
    }

    if(endLine)
        mParameters += name +": \t"+value +"\n";
    else
        mParameters += name +": \t"+value +"   ";
}
