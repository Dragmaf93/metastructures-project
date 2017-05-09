#include "StartSimulationPage.h"

StartSimulationPage::StartSimulationPage()
    :AbstractPage(START_SIMULATION)
{
    this->setTitle("Start Simulation");

    setButtonText(QWizard::NextButton,QString("Start"));
    setButtonText(QWizard::CancelButton,QString("Continue to add simulations"));

    mDirectoryInput = new QLineEdit;
    mExplorerButton = new QPushButton("Search");
    mFileDialog = new QFileDialog(this);

    mFileDialog->setDirectory("C:\\Users\\manue\\Sviluppo\\SimulationData");
    mDirectoryInput->setText("C:\\Users\\manue\\Sviluppo\\SimulationData");
    mDirectoryInput->setFocusPolicy(Qt::FocusPolicy::NoFocus);
    QLabel* folderLabel = new QLabel("Folder");

    QVBoxLayout* rootLayout = new QVBoxLayout;
    QHBoxLayout* folderLayout = new QHBoxLayout;

    folderLayout->addWidget(folderLabel);
    folderLayout->addWidget(mDirectoryInput);
    folderLayout->addWidget(mExplorerButton);

    rootLayout->addLayout(folderLayout);
    this->setLayout(rootLayout);

    connect(mExplorerButton,SIGNAL(clicked(bool)),this,SLOT(showFileDialog()));
}

int StartSimulationPage::nextId() const
{
    return PAGE_TYPE::SIMULATION_RUNNING;
}

void StartSimulationPage::initializePage()
{
    AbstractPage::initializePage();
    emit nextPage(START_SIMULATION);
}

void StartSimulationPage::cleanupPage()
{
    AbstractPage::cleanupPage();
    emit nextPage(OBSTACLES_CONFIG);
}

void StartSimulationPage::setCsvDataLogger(FlockSimulator::CsvDataLogger *csvLogger)
{
    mCsvLogger = csvLogger;
    mCsvLogger->setDirectory(mDirectoryInput->text());
}

void StartSimulationPage::showFileDialog()
{
    QString dir = mFileDialog->getExistingDirectory();
    mDirectoryInput->setText(dir);
    mCsvLogger->setDirectory(mDirectoryInput->text());
}
