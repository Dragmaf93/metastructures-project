#ifndef RANDOMSIMULATIONPAGE_H
#define RANDOMSIMULATIONPAGE_H

#include "AbstractPage.h"
#include <QSpinBox>
#include <QFormLayout>
#include <QLabel>
#include <QSpacerItem>

class RandomSimulationPage : public AbstractPage{
    Q_OBJECT
public:
    RandomSimulationPage();
    void setParameterSimulation(FlockSimulator::ParameterSimulation &parameter, QVector<FlockSimulator::ParameterSimulation> &pVector);
    int nextId()const;
private:
    QSpinBox* mNumSimulationInput;
    QSpinBox* mSeedInput;

    QSpinBox* mRangeNumBoidsLInput;
    QSpinBox* mRangeNumBoidsUInput;

    QDoubleSpinBox* mRangeMinXLInput;
    QDoubleSpinBox* mRangeMinXUInput;
    QDoubleSpinBox* mRangeMaxXLInput;
    QDoubleSpinBox* mRangeMaxXUInput;
    QDoubleSpinBox* mRangeMinZLInput;
    QDoubleSpinBox* mRangeMinZUInput;
    QDoubleSpinBox* mRangeMaxZLInput;
    QDoubleSpinBox* mRangeMaxZUInput;

    int getRandomInt(int min, int max, unsigned seed);
    float getRandomFloat(float min, float max, unsigned seed);

    QSpinBox* createQSpinBox(int defVal = 0)const;
    QDoubleSpinBox* createQDoubleSpinBox(float defVal =0.0f)const;

};

#endif // RANDOMSIMULATIONPAGE_H
