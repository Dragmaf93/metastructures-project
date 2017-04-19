#ifndef ABSTRACTPAGE_H
#define ABSTRACTPAGE_H

#include <QWizardPage>
#include <QMessageBox>
#include <src/ParameterSimulation.h>
#include<QDebug>

class AbstractPage: public QWizardPage{
    Q_OBJECT
public:
    enum PAGE_TYPE{DATABASE, GENERAL_CONFIG,FLOCKS_CONFIG,
                  OBSTACLES_CONFIG,START_SIMULATION,
                  SIMULATION_RUNNING,RANDOM_SIM_PAGE,LAST_PAGE};

    AbstractPage(PAGE_TYPE type);
    virtual void setParameterSimulation(FlockSimulator::ParameterSimulation &parameter,
                                         QVector<FlockSimulator::ParameterSimulation>& pVector) = 0;

    void initializePage(){mViewed = true;}
    void cleanupPage(){mViewed = false;}

protected:
    bool mViewed;
    PAGE_TYPE mType;
    const QString DFILE_PATH=":/resources/dfile.xml";
protected slots:
    void pageChanged();
signals:
    void nextPage(AbstractPage::PAGE_TYPE)const;
};

#endif // ABSTRACTPAGE_H

