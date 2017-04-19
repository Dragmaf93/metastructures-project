#ifndef SIMULATIONINPROGRESSPAGE_H
#define SIMULATIONINPROGRESSPAGE_H

#include"AbstractPage.h"

#include<QLabel>
#include <QTextEdit>
#include<QVBoxLayout>

class SimulationInProgressPage: public AbstractPage{
    Q_OBJECT
public:

    SimulationInProgressPage();
    void setParameterSimulation(FlockSimulator::ParameterSimulation &parameter,QVector<FlockSimulator::ParameterSimulation>& pVector){}
    void initializePage();
    int nextId()const;

private:
    QTextEdit* mTextEdit;

public slots:
    void readOutput(QString string);
    void readError(QString string);



};

#endif // SIMULATIONINPROGRESSPAGE_H
