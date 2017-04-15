#include "RandomSimulationPage.h"
#include <qglobal.h>
#include <QDebug>

RandomSimulationPage::RandomSimulationPage()
    : AbstractPage(RANDOM_SIM_PAGE)
{
    this->setTitle("Setting multiple simulations");

    mNumSimulationInput = createQSpinBox(1);
    mSeedInput = createQSpinBox(1);

    mRangeNumBoidsLInput =  createQSpinBox(50);
    mRangeNumBoidsUInput = createQSpinBox(100);

    mRangeMinXLInput = createQDoubleSpinBox(-20.0f);
    mRangeMinXUInput = createQDoubleSpinBox(20.0f);
    mRangeMaxXLInput = createQDoubleSpinBox(20.0f);
    mRangeMaxXUInput = createQDoubleSpinBox(40.0f);
    mRangeMinZLInput = createQDoubleSpinBox(-5.0f);
    mRangeMinZUInput =  createQDoubleSpinBox(5.0f);
    mRangeMaxZLInput =  createQDoubleSpinBox(5.0f);
    mRangeMaxZUInput =  createQDoubleSpinBox(15.0f);

    QVBoxLayout* rootLayout = new QVBoxLayout;
    QFormLayout* firstFormLayout = new QFormLayout;

    QHBoxLayout* flocksLayout = new QHBoxLayout;
    QFormLayout* formLayoutMinL = new QFormLayout;
    QFormLayout* formLayoutMinU = new QFormLayout;
    QFormLayout* formLayoutMaxL = new QFormLayout;
    QFormLayout* formLayoutMaxU = new QFormLayout;

    firstFormLayout->addRow(new QLabel("Number of simulations"), mNumSimulationInput);
    firstFormLayout->addRow(new QLabel("Seed"), mSeedInput);

    rootLayout->addLayout(firstFormLayout);
    rootLayout->addWidget(new QLabel("Flocks"));
    formLayoutMinL->addRow(new QLabel("Range boids number"),mRangeNumBoidsLInput);
    formLayoutMinU->addRow(new QLabel("-"),mRangeNumBoidsUInput);
    formLayoutMaxL->addItem(new QSpacerItem(10000, 20, QSizePolicy::Expanding, QSizePolicy::Expanding));
    formLayoutMaxU->addItem(new QSpacerItem(10000, 20, QSizePolicy::Expanding, QSizePolicy::Expanding));

    formLayoutMinL->addRow(new QLabel("Range MinX"),mRangeMinXLInput);
    formLayoutMinU->addRow(new QLabel("-"),mRangeMinXUInput);
    formLayoutMaxL->addRow(new QLabel("Range MaxX"),mRangeMaxXLInput);
    formLayoutMaxU->addRow(new QLabel("-"),mRangeMaxXUInput);
    formLayoutMinL->addRow(new QLabel("Range MinZ"),mRangeMinZLInput);
    formLayoutMinU->addRow(new QLabel("-"),mRangeMinZUInput);
    formLayoutMaxL->addRow(new QLabel("Range MaxZ"),mRangeMaxZLInput);
    formLayoutMaxU->addRow(new QLabel("-"),mRangeMaxZUInput);


    flocksLayout->addLayout(formLayoutMinL);
    flocksLayout->addLayout(formLayoutMinU);
    flocksLayout->addLayout(formLayoutMaxL);
    flocksLayout->addLayout(formLayoutMaxU);

    rootLayout->addLayout(flocksLayout);
    this->setLayout(rootLayout);

}

void RandomSimulationPage::setParameterSimulation(FlockSimulator::ParameterSimulation &parameter, QVector<FlockSimulator::ParameterSimulation>& pVector)
{
   unsigned seed = mSeedInput->value();
   unsigned numSimulation = mNumSimulationInput->value();
   for(int i = 0; i < numSimulation; i++){

       FlockSimulator::ParameterSimulation p(parameter);
       FlockSimulator::ParameterSimulation::Flock flock;

       flock.numBoids = getRandomInt(mRangeNumBoidsLInput->value(),mRangeNumBoidsUInput->value(),seed*i);
       flock.xMin = getRandomFloat(mRangeMinXLInput->value(),mRangeMinXUInput->value(),seed*i);
       flock.xMax = getRandomFloat(mRangeMaxXLInput->value(),mRangeMaxXUInput->value(),seed*i);
       flock.zMin= getRandomFloat(mRangeMinZLInput->value(),mRangeMinZUInput->value(),seed*i);
       flock.zMax = getRandomFloat(mRangeMaxZLInput->value(),mRangeMaxZUInput->value(),seed*i);
       qDebug()<< flock.xMin;
       p.clearFlocks();
       p.addFlock(flock);

       pVector.append(p);

   }
}

int RandomSimulationPage::nextId() const
{
    return PAGE_TYPE::START_SIMULATION;
}

int RandomSimulationPage::getRandomInt(int min, int max, unsigned seed)
{
    qsrand(seed);
    int num = qrand() % ((max+1) -min) + min;
    return num;
}

float RandomSimulationPage::getRandomFloat(float min, float max, unsigned seed)
{
    qsrand(seed);
    float num = qrand() % (int)((max+1.0f) - min) + min;
    return num;
}

QSpinBox *RandomSimulationPage::createQSpinBox(int defVal) const
{
    QSpinBox* spinI = new QSpinBox;
    spinI->setMaximum(999);
    spinI->setMinimum(0);
    spinI->setValue(defVal);
    return spinI;

}

QDoubleSpinBox *RandomSimulationPage::createQDoubleSpinBox(float defVal) const
{
    QDoubleSpinBox* spinF = new QDoubleSpinBox;
    spinF->setMaximum(999);
    spinF->setMinimum(-999);
    spinF->setValue(defVal);
    return spinF;
}

