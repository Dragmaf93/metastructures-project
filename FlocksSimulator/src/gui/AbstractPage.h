#ifndef ABSTRACTPAGE_H
#define ABSTRACTPAGE_H

#include <QWizard>
#include <src/ParameterSimulation.h>
#include<QDebug>

class AbstractPage: public QWizardPage{
    Q_OBJECT
public:
    enum PAGE_TYPE{DATABASE, GENERAL_CONFIG,FLOCKS_CONFIG,
                  OBSTACLES_CONFIG,START_SIMULATION,
                  SIMULATION_RUNNING,LAST_PAGE};

    AbstractPage(PAGE_TYPE type);
    virtual void setParameterSimulation(FlockSimulator::ParameterSimulation &parameter) = 0;
    virtual void initializePage();
protected:
    PAGE_TYPE mType;
    const QString DFILE_PATH=":/resources/dfile.xml";
protected slots:
    void pageChanged();
signals:
    void nextPage(AbstractPage::PAGE_TYPE);
};

#endif // ABSTRACTPAGE_H

