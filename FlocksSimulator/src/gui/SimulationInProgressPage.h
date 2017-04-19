#ifndef SIMULATIONINPROGRESSPAGE_H
#define SIMULATIONINPROGRESSPAGE_H

#include"AbstractPage.h"
#include"../SimulatorsManager.h"

#include<QLabel>
#include <QTextEdit>
#include<QVBoxLayout>
#include<QProgressBar>
#include<QThread>

class SimulationInProgressPage: public AbstractPage{
    Q_OBJECT

friend class ProgressBarUpdater;
public:

    SimulationInProgressPage();
    void setParameterSimulation(FlockSimulator::ParameterSimulation &parameter,QVector<FlockSimulator::ParameterSimulation>& pVector){}
    void initializePage();

    int nextId()const;
    bool isComplete()const;

    void simulationsStarted();
    void setSimulator(FlockSimulator::SimulatorsManager &s);
    void simulationEnded();
private:
    QTextEdit* mTextEdit;
    QProgressBar* mProgressBar;
    bool mSimulationEnded;
    FlockSimulator::SimulatorsManager* mSimulator;

public slots:
    void readOutput(QString string);
    void readError(QString string);
    void updateProgressBar();
};
#endif // SIMULATIONINPROGRESSPAGE_H
