#ifndef DATABASEPAGE_H
#define DATABASEPAGE_H

#include "AbstractPage.h"

#include <QLineEdit>
#include <QSpinBox>
#include <QTextEdit>
#include <QFormLayout>
#include <QLabel>
#include <QXmlQuery>

#include "src/DatabaseLogger.h"

class DatabasePage : public AbstractPage{
    Q_OBJECT
public:
    DatabasePage();

    void setParameterSimulation(FlockSimulator::ParameterSimulation &parameter,QVector<FlockSimulator::ParameterSimulation>& pVector){}
    void setDatabaseLogger(FlockSimulator::DatabaseLogger* dbLogger);

    bool isComplete()const;
    void setDatabase();
    bool validatePage();

private:
    QLineEdit* mHostInput;
    QLineEdit* mUserInput;
    QLineEdit* mDbNameInput;
    QLineEdit* mPasswordInput;
    QLineEdit* mPortInput;

    QPushButton* mTestButton;

    void loadDefaultValues();
    FlockSimulator::DatabaseLogger* mDbLogger;
};

#endif // DATABASEPAGE_H
