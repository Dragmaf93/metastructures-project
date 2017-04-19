#include "ConfigSimulationPage.h"

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

    mMultipleSimulationsRB = new QRadioButton("Multiple random simulations");
    mSingleSimulationRB = new QRadioButton("Single custom simulation");

    mForceSpaceInput->setValue(DEFAULT_FORCE_OR);
    mRadiusSpaceInput->setValue(DEFAULT_RADIUS_OR);
    mRandomSeedInput->setValue(DEFAULT_RANDOM_SEED);
    mTimeLimitInput->setValue(DEFAULT_TIME_LIMIT_SEC);
    mTimeStepInput->setValue(DEFAULT_TIME_STEP_MSEC);

    formLayoutL->addRow(new QLabel("Time limit in seconds"),mTimeLimitInput);
    formLayoutR->addRow(new QLabel("Time step in milliseconds"),mTimeStepInput);
    formLayoutL->addRow(new QLabel("Space constraint radius"),mRadiusSpaceInput);
    formLayoutR->addRow(new QLabel("Space constraint force"),mForceSpaceInput);
    formLayoutL->addRow(new QLabel("Randomization seed"),mRandomSeedInput);
    formLayoutR->addRow(new QLabel(" "));
    formLayoutL->addRow( mSingleSimulationRB);
    formLayoutR->addRow( mMultipleSimulationsRB);
    QFormLayout* topLayout = new QFormLayout();

    mSingleSimulationRB->setChecked(true);

    mNameInput = new QLineEdit;
    mLabelInput = new QLineEdit;
    mDescriptionInput = new QTextEdit;

    mNameInput->setText("Simulation");
    mLabelInput->setText("Circular");

    topLayout->addRow(new QLabel("Name"),mNameInput);
    topLayout->addRow(new QLabel("Label"),mLabelInput);
    topLayout->addRow(new QLabel("Description"),mDescriptionInput);

    rootLayout->addLayout(topLayout,1);
    rootLayout->addLayout(bottomLayout,2);

    rootLayout->setSpacing(30);
    bottomLayout->setSpacing(15);
    topLayout->setSpacing(15);

    connect(mNameInput, SIGNAL(textChanged(QString)),this, SLOT(pageChanged()));
    connect(mLabelInput, SIGNAL(textChanged(QString)),this, SLOT(pageChanged()));
}


void ConfigSimulationPage::setParameterSimulation(FlockSimulator::ParameterSimulation &parameter, QVector<FlockSimulator::ParameterSimulation> &pVector)
{
    if(!mViewed) return;
    qDebug() <<"ConfigPage";

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

int ConfigSimulationPage::nextId() const
{
    if(mSingleSimulationRB->isChecked()) return PAGE_TYPE::FLOCKS_CONFIG;
    if(mMultipleSimulationsRB->isChecked()) return PAGE_TYPE::RANDOM_SIM_PAGE;
}
