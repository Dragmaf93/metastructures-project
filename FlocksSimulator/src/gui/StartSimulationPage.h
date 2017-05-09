#ifndef STARTSIMULATIONPAGE_H
#define STARTSIMULATIONPAGE_H

#include"AbstractPage.h"
#include "../CsvDatalogger.h"

#include <QLineEdit>
#include <QSpinBox>
#include <QTextEdit>
#include <QFormLayout>
#include <QLabel>
#include <QPushButton>
#include <QFileDialog>

class StartSimulationPage: public AbstractPage{
    Q_OBJECT
public:
    StartSimulationPage();

    void setParameterSimulation(FlockSimulator::ParameterSimulation &parameter,QVector<FlockSimulator::ParameterSimulation>& pVector){}
    int nextId()const;
    void initializePage();
    void cleanupPage();

    void setCsvDataLogger(FlockSimulator::CsvDataLogger* csvLogger);
private:
    QLineEdit* mDirectoryInput;
    QPushButton* mExplorerButton;
    QFileDialog* mFileDialog;

   FlockSimulator::CsvDataLogger* mCsvLogger;
private slots:
    void showFileDialog();
};
#endif // STARTSIMULATIONPAGE_H
