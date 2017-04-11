#ifndef OBSTACLESCONFIGPAGE_H
#define OBSTACLESCONFIGPAGE_H

#include"AbstractPage.h"

#include<QPushButton>
#include<QLabel>
#include<QSpinBox>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QPixmap>
#include <QIcon>

class ObstacleDialog;
class ObstacleItem;

class ObstacleConfigPage : public AbstractPage{
    Q_OBJECT

public:
    explicit ObstacleConfigPage();
    void setParameterSimulation(FlockSimulator::ParameterSimulation &parameter);
private:
    QPushButton* mAddObstaclesButton;
    ObstacleDialog* mObstacleDialog;
    QObject* mLastDialogCaller;

    QList<ObstacleItem*> mObstacleItems;
    QVBoxLayout* mObstaclesListLayout;
    void addObstacleItem(FlockSimulator::ParameterSimulation::Obstacle &obstacle);
signals:

private slots:
    void showObstacleDialog();
    void closeObstacleDialog(int result);
    void deleteObstaclesItem();
};

class ObstacleDialog: public QDialog{
    Q_OBJECT
public:
    ObstacleDialog(FlockSimulator::ParameterSimulation::Obstacle &obstacle);
    FlockSimulator::ParameterSimulation::Obstacle getObstacle()const {return mObstacle;}
public slots:
    void commitObstacleUpdate();
private:
    QLabel* mObstacleLabel;
    QDoubleSpinBox* mCenterXInput;
    QDoubleSpinBox* mCenterYInput;
    QDoubleSpinBox* mCenterZInput;
    QDoubleSpinBox* mRadiusInput;
    QPushButton* mCommitButton;

    FlockSimulator::ParameterSimulation::Obstacle mObstacle;
};

class ObstacleItem: public QWidget{
    Q_OBJECT
    friend class ObstacleConfigPage;
public:

    ObstacleItem(FlockSimulator::ParameterSimulation::Obstacle &obstacle);

    FlockSimulator::ParameterSimulation::Obstacle getObstacle()const{return mObstacle;}

    void disableButtons(bool b);
private:
    QPushButton* mDeleteButton;
    QPushButton* mUpdateButton;
    QLabel* mCenterXLabel;
    QLabel* mCenterYLabel;
    QLabel* mCenterZLabel;
    QLabel* mRadiusLabel;

    FlockSimulator::ParameterSimulation::Obstacle mObstacle;

public slots:
    void updateItem(FlockSimulator::ParameterSimulation::Obstacle &obstacle);

};
#endif // OBSTACLESCONFIGPAGE_H
