#include "DatabasePage.h"
#include <QFile>
#include<QRegularExpressionValidator>

DatabasePage::DatabasePage()
    :AbstractPage(DATABASE)
{
    this->setTitle("Database connection");

    mPasswordInput = new QLineEdit;
    mHostInput = new QLineEdit;
    mDbNameInput = new QLineEdit;
    mUserInput = new QLineEdit;
    mPortInput = new QLineEdit;

    QString oIpRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
    QRegularExpression rx("^" + oIpRange
                          + "\\." + oIpRange
                          + "\\." + oIpRange
                          + "\\." + oIpRange + "$");

    QValidator *validator = new QRegularExpressionValidator(rx, this);

    mHostInput->setValidator(validator);

    QVBoxLayout* rootLayout = new QVBoxLayout();

    QHBoxLayout* firstRowLayout = new QHBoxLayout();

    QFormLayout* formL = new QFormLayout();
    formL->setSpacing(45);
    formL->addRow(new QLabel("Host"),mHostInput);
    QFormLayout* formR = new QFormLayout();
    formR->addRow(new QLabel("Port"),mPortInput);
    firstRowLayout-> addLayout(formL,4);
    firstRowLayout-> addLayout(formR,1);

    QFormLayout* formLayout = new QFormLayout;
    formLayout->addRow(new QLabel("Database"),mDbNameInput);
    formLayout->addRow(new QLabel("User"),mUserInput);
    formLayout->addRow(new QLabel("Passaword"),mPasswordInput);


    rootLayout->addLayout(firstRowLayout);
    rootLayout->addLayout(formLayout);
    this->setLayout(rootLayout);

    connect(mPasswordInput, SIGNAL(textChanged(QString)),this, SLOT(pageChanged()));
    connect(mUserInput, SIGNAL(textChanged(QString)),this, SLOT(pageChanged()));
    connect(mDbNameInput, SIGNAL(textChanged(QString)),this, SLOT(pageChanged()));
    connect(mHostInput, SIGNAL(textChanged(QString)),this, SLOT(pageChanged()));
    connect(mPortInput, SIGNAL(textChanged(QString)),this, SLOT(pageChanged()));

    loadDefaultValues();
}

void DatabasePage::setDatabaseLogger(FlockSimulator::DatabaseLogger *dbLogger)
{
    mDbLogger=dbLogger;
}

bool DatabasePage::isComplete() const
{

    bool hostCorrect = mHostInput->text().count(".") > 2;

    if(mHostInput->text().isEmpty() ||
            mDbNameInput->text().isEmpty()||
            mUserInput->text().isEmpty() ||
            mPortInput->text().isEmpty() ||
            !hostCorrect
            ) return false;

    return true;
}

void DatabasePage::loadDefaultValues()
{
    QFile file(DFILE_PATH);

    if(!file.open(QIODevice::ReadOnly)){}
    QXmlQuery query;
    QString result;
    query.setFocus(&file);

    query.setQuery("default-values/db-page/host/text()");
    query.evaluateTo(&result);
    result.chop(1);
    mHostInput->setText(result);

    query.setQuery("default-values/db-page/port/text()");
    query.evaluateTo(&result);
    result.chop(1);
    mPortInput->setText(result);

    query.setQuery("default-values/db-page/name/text()");
    query.evaluateTo(&result);
    result.chop(1);
    mDbNameInput->setText(result);

    query.setQuery("default-values/db-page/user/text()");
    query.evaluateTo(&result);
    result.chop(1);
    mUserInput->setText(result);

    mPasswordInput->setText("19max-viz93");
}

void DatabasePage::setDatabase()
{
    mDbLogger->setDatabaseHost(mHostInput->text());
    mDbLogger->setDatabaseUser(mUserInput->text());
    mDbLogger->setDatabaseName(mDbNameInput->text());
    mDbLogger->setDatabasePassword(mPasswordInput->text());
    mDbLogger->setDatabasePort(mPortInput->text().toInt());
}

