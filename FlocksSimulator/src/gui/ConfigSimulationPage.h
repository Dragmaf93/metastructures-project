#ifndef CONFIGSIMULATIONPAGE_H
#define CONFIGSIMULATIONPAGE_H

#include "AbstractPage.h"

#include <QLineEdit>
#include <QSpinBox>
#include <QTextEdit>

class ConfigSimulationPage : public AbstractPage{
    Q_OBJECT

public:
    ConfigSimulationPage();
    void setParameterSimulation(FlockSimulator::ParameterSimulation &parameter);
    bool isComplete()const;
private:
    QDoubleSpinBox* mRadiusSpaceInput;
    QDoubleSpinBox* mForceSpaceInput;
    QSpinBox* mTimeLimitInput;
    QSpinBox* mTimeStepInput;
    QSpinBox* mRandomSeedInput;

    QLineEdit* mNameInput;
    QLineEdit* mLabelInput;
    QTextEdit* mDescriptionInput;

};

#endif // CONFIGSIMULATIONPAGE_H
