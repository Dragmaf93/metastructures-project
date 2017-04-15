#ifndef CONFIGSIMULATIONPAGE_H
#define CONFIGSIMULATIONPAGE_H

#include "AbstractPage.h"

#include <QLineEdit>
#include <QSpinBox>
#include <QTextEdit>
#include <QRadioButton>
#include <QFormLayout>
#include <QLabel>

class ConfigSimulationPage : public AbstractPage{
    Q_OBJECT

public:
    ConfigSimulationPage();
    void setParameterSimulation(FlockSimulator::ParameterSimulation &parameter,
                                QVector<FlockSimulator::ParameterSimulation>& pVector);
    bool isComplete()const;
    int nextId()const;

private:
    QDoubleSpinBox* mRadiusSpaceInput;
    QDoubleSpinBox* mForceSpaceInput;
    QSpinBox* mTimeLimitInput;
    QSpinBox* mTimeStepInput;
    QSpinBox* mRandomSeedInput;

    QLineEdit* mNameInput;
    QLineEdit* mLabelInput;
    QTextEdit* mDescriptionInput;

    QRadioButton* mMultipleSimulationsRB;
    QRadioButton* mSingleSimulationRB;

};

#endif // CONFIGSIMULATIONPAGE_H
