#include "ConfigSimulationPage.h"

#include <QFormLayout>
#include <QLabel>

ConfigSimulationPage::ConfigSimulationPage()
    :AbstractPage(GENERAL_CONFIG)
{
    this->setTitle("Setting simulation parameter");

    QVBoxLayout* rootLayout = new QVBoxLayout;

    this->setLayout(rootLayout);
    QHBoxLayout* bottomLayout = new QHBoxLayout;
    QFormLayout* formLayoutR = new QFormLayout;
    QFormLayout* formLayoutL = new QFormLayout;

    bottomLayout->addLayout(formLayoutL);
    bottomLayout->addLayout(formLayoutR);

    mForceSpaceInput = new QDoubleSpinBox;
    mRadiusSpaceInput = new QDoubleSpinBox;
    mRandomSeedInput = new QSpinBox;
    mTimeLimitInput = new QSpinBox;
    mTimeStepInput = new QSpinBox;

    mForceSpaceInput->setValue(DEFAULT_FORCE_OR);
    mRadiusSpaceInput->setValue(DEFAULT_RADIUS_OR);
    mRandomSeedInput->setValue(DEFAULT_RANDOM_SEED);
    mTimeLimitInput->setValue(DEFAULT_TIME_LIMIT_SEC);
    mTimeStepInput->setValue(DEFAULT_TIME_STEP_MSEC);

    formLayoutL->addRow(new QLabel("<b>Time limit in seconds</b>"),mTimeLimitInput);
    formLayoutR->addRow(new QLabel("<b>Time step in milliseconds</b>"),mTimeStepInput);
    formLayoutR->addRow(new QLabel("<b>Space constraint force</b>"),mForceSpaceInput);
    formLayoutL->addRow(new QLabel("<b>Space constraint radius</b>"),mRadiusSpaceInput);
    formLayoutL->addRow(new QLabel("<b>Randomization seed</b>"),mRandomSeedInput);

    QFormLayout* topLayout = new QFormLayout();

    mNameInput = new QLineEdit;
    mLabelInput = new QLineEdit;
    mDescriptionInput = new QTextEdit;

    mNameInput->setText("Simulation");
    mLabelInput->setText("Circular");

    topLayout->addRow(new QLabel("<b>Name</b>"),mNameInput);
    topLayout->addRow(new QLabel("<b>Label</b>"),mLabelInput);
    topLayout->addRow(new QLabel("<b>Description</b>"),mDescriptionInput);

    rootLayout->addLayout(topLayout,1);
    rootLayout->addLayout(bottomLayout,2);

    rootLayout->setSpacing(30);
    bottomLayout->setSpacing(15);
    topLayout->setSpacing(15);

    connect(mNameInput, SIGNAL(textChanged(QString)),this, SLOT(pageChanged()));
    connect(mLabelInput, SIGNAL(textChanged(QString)),this, SLOT(pageChanged()));
}


void ConfigSimulationPage::setParameterSimulation(FlockSimulator::ParameterSimulation &parameter)
{
    parameter.setForceSpace(mForceSpaceInput->value());
    parameter.setRadiusSpace(mRadiusSpaceInput->value());
    parameter.setRandomSeed(mRandomSeedInput->value());
    parameter.setTimeLimit(mTimeLimitInput->value());
    parameter.setTimeStep(mTimeStepInput->value());
    parameter.setSimulationDescription(mDescriptionInput->toPlainText());
    parameter.setSimulationLabel(mLabelInput->text());
    parameter.setSimulationName(mNameInput->text());
}

bool ConfigSimulationPage::isComplete() const
{
    if(mNameInput->text().isEmpty()
            || mLabelInput->text().isEmpty()) return false;
    return true;
}
