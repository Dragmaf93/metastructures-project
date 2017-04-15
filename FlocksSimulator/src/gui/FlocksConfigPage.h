#ifndef FLOKCSANDOBSTACLESCONFIGURATIONPAGE_H
#define FLOKCSANDOBSTACLESCONFIGURATIONPAGE_H

#include"AbstractPage.h"

#include <QPushButton>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QPixmap>
#include <QIcon>
class FlockDialog;
class FlockItem;

class FlocksConfigPage : public AbstractPage{
    Q_OBJECT


public:
    FlocksConfigPage();
    void setParameterSimulation(FlockSimulator::ParameterSimulation &parameter,QVector<FlockSimulator::ParameterSimulation>& pVector);

private:
    QPushButton* mAddFlocksButton;
    FlockDialog* mFlockDialog;
    QObject* mLastDialogCaller;

    QList<FlockItem*> mFlockItems;
    QVBoxLayout* mFlocksListLayout;
    void addFlockItem(FlockSimulator::ParameterSimulation::Flock &flock);

private slots:
    void showFlockDialog();
    void closeFlockDialog(int result);
    void deleteFlockItem();
};

class FlockDialog: public QDialog{
    Q_OBJECT
public:
    FlockDialog(FlockSimulator::ParameterSimulation::Flock &flock);
    FlockSimulator::ParameterSimulation::Flock getFlock()const {return mFlock;}
public slots:
    void commitFlockUpdate();
private:
    QLabel* mFlockLabel;
    QSpinBox* mBoidsNumInput;
    QSpinBox* mBoidsSpecieInput;
    QDoubleSpinBox* mMinXInput;
    QDoubleSpinBox* mMaxXInput;
    QDoubleSpinBox* mMinZInput;
    QDoubleSpinBox* mMaxZInput;
    QPushButton* mCommitButton;

    FlockSimulator::ParameterSimulation::Flock mFlock;
};

class FlockItem: public QWidget{
    Q_OBJECT
    friend class FlocksConfigPage;
public:

    FlockItem(FlockSimulator::ParameterSimulation::Flock &flock);

    FlockSimulator::ParameterSimulation::Flock getFlock()const{return mFlock;}

    void disableButtons(bool b);
private:
    QPushButton* mDeleteButton;
    QPushButton* mUpdateButton;
    QLabel* mNumBoidLabel;
    QLabel* mSpecieLabel;
    QLabel* mMinXLabel;
    QLabel* mMaxXLabel;
    QLabel* mMaxZLabel;
    QLabel* mMinZLabel;



    FlockSimulator::ParameterSimulation::Flock mFlock;

public slots:
    void updateItem(FlockSimulator::ParameterSimulation::Flock &flock);

};

#endif // FLOKCSANDOBSTACLESCONFIGURATIONPAGE_H
