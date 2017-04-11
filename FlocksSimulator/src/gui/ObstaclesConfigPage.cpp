#include "ObstaclesConfigPage.h"
#include<QDebug>
ObstacleConfigPage::ObstacleConfigPage()
    : AbstractPage(OBSTACLES_CONFIG)
{
    mAddObstaclesButton = new QPushButton("+");

    QPixmap pixmap(":/resources/icons/add.png");
    QIcon buttonIcon(pixmap);
    mAddObstaclesButton->setIcon(buttonIcon);

    mAddObstaclesButton->setFixedSize(QSize(32,32));
    mAddObstaclesButton->setFlat(true);

    QVBoxLayout* rootLayout = new QVBoxLayout;

    QVBoxLayout* topLayout = new QVBoxLayout;

    QHBoxLayout*  headerLayoutFlock= new QHBoxLayout;

    headerLayoutFlock->addWidget(new QLabel("<h3>Obstacle</h3>"));
    headerLayoutFlock->addWidget(mAddObstaclesButton);

    mObstaclesListLayout = new QVBoxLayout;

    QWidget* headerWidget = new QWidget();
    headerWidget->setObjectName("headerWidget");
    headerWidget->setLayout(headerLayoutFlock);
    headerWidget->setStyleSheet("QWidget#headerWidget{background-color:#EEEEEE;"
                                " border-bottom: 1px solid grey;"
                                "}");
    QWidget* listWidget = new QWidget();
    listWidget->setLayout(mObstaclesListLayout);

    rootLayout->addWidget(headerWidget);
    rootLayout->addWidget(listWidget);

    QWidget* rootWidget = new QWidget();
    rootWidget->setLayout(rootLayout);
    rootWidget->setObjectName("obstaclesRootWidget");
    rootWidget->setStyleSheet("#obstaclesRootWidget{border: 1px solid grey;}");
    rootLayout->setContentsMargins(0,0,0,0);
    QHBoxLayout* layout = new QHBoxLayout();
    layout->addWidget(rootWidget);

    this->setTitle("Setting obstacles");
    this->setLayout(layout);

    connect(mAddObstaclesButton,SIGNAL(released()),this,SLOT(showObstacleDialog()));

}

void ObstacleConfigPage::setParameterSimulation(FlockSimulator::ParameterSimulation &parameter)
{
    foreach (ObstacleItem* item, mObstacleItems) {
        FlockSimulator::ParameterSimulation::Obstacle o = item->getObstacle();
        parameter.addObstacle(o);
    }
}

void ObstacleConfigPage::addObstacleItem(FlockSimulator::ParameterSimulation::Obstacle &obstacle)
{
    ObstacleItem* item = new ObstacleItem(obstacle);
    mObstacleItems.append(item);
    mObstaclesListLayout->addWidget(item);
    connect(item->mUpdateButton,SIGNAL(released()),this,SLOT(showObstacleDialog()));
    connect(item->mDeleteButton,SIGNAL(released()),this,SLOT(deleteObstaclesItem()));

    if(mObstacleItems.length()==4)
        mAddObstaclesButton->setDisabled(true);
    else
        mAddObstaclesButton->setDisabled(false);

}

void ObstacleConfigPage::showObstacleDialog()
{
    mAddObstaclesButton->setDisabled(true);
    foreach(ObstacleItem* item, mObstacleItems)
        item->disableButtons(true);

    mLastDialogCaller = QObject::sender();

    if(mLastDialogCaller == mAddObstaclesButton){
        FlockSimulator::ParameterSimulation::Obstacle obstacle;
        mObstacleDialog=new ObstacleDialog(obstacle);
    }else{
        ObstacleItem* item = (ObstacleItem*)mLastDialogCaller->parent();
        FlockSimulator::ParameterSimulation::Obstacle obstacle = item->getObstacle();
        mObstacleDialog=new ObstacleDialog(obstacle);
    }
    connect(mObstacleDialog,SIGNAL(finished(int)),this, SLOT(closeObstacleDialog(int)));
    mObstacleDialog->show();
}

void ObstacleConfigPage::closeObstacleDialog(int result)
{
    if(result == QDialog::Rejected){

    }else{

        if(mLastDialogCaller == mAddObstaclesButton){
            FlockSimulator::ParameterSimulation::Obstacle obstacle = mObstacleDialog->getObstacle();
            addObstacleItem(obstacle);
        }else{
            ObstacleItem* item = (ObstacleItem*)mLastDialogCaller->parent();
            FlockSimulator::ParameterSimulation::Obstacle obstacle = mObstacleDialog->getObstacle();
            item->updateItem(obstacle);
        }

    }
    if(mObstacleItems.length()<4)
        mAddObstaclesButton->setDisabled(false);

    foreach(ObstacleItem* item, mObstacleItems)
        item->disableButtons(false);

    delete mObstacleDialog;
    mLastDialogCaller = nullptr;
    mObstacleDialog = nullptr;
}

void ObstacleConfigPage::deleteObstaclesItem()
{
    QObject* obj = QObject::sender();
    ObstacleItem* item = (ObstacleItem *)obj->parent();

    mObstacleItems.removeOne(item);
    mObstaclesListLayout->removeWidget(item);
    delete item;

    if(mObstacleItems.length()<4)
        mAddObstaclesButton->setDisabled(false);
}

ObstacleDialog::ObstacleDialog(FlockSimulator::ParameterSimulation::Obstacle &obstacle)
{
    mObstacleLabel = new QLabel();
    mCenterXInput = new QDoubleSpinBox;
    mCenterYInput = new QDoubleSpinBox;
    mCenterZInput = new QDoubleSpinBox;
    mRadiusInput = new QDoubleSpinBox;
    mCommitButton = new QPushButton("Ok");

    mObstacle = obstacle;

    mCenterXInput->setValue(mObstacle.x);
    mCenterYInput->setValue(mObstacle.y);
    mCenterZInput->setValue(mObstacle.z);
    mRadiusInput->setValue(mObstacle.radius);

    QVBoxLayout* rootLayout = new QVBoxLayout;

    QHBoxLayout* headerLayout = new QHBoxLayout;
    headerLayout->addWidget(new QLabel("<h4>Obstacle</h4>"));
    headerLayout->addWidget(mObstacleLabel);
    QHBoxLayout* centralLayout = new QHBoxLayout;

    QFormLayout* formLayoutR = new QFormLayout;

    formLayoutR->addRow(new QLabel("<b>Center x</b>"),mCenterXInput);
    formLayoutR->addRow(new QLabel("<b>Center y</b>"),mCenterYInput);
    formLayoutR->addRow(new QLabel("<b>Center z</b>"),mCenterZInput);
    formLayoutR->addRow(new QLabel("<b>Radius</b>"),mRadiusInput);

    centralLayout->addLayout(formLayoutR);

    rootLayout->addLayout(headerLayout);
    rootLayout->addLayout(centralLayout);

    rootLayout->addWidget(mCommitButton);

    rootLayout->setSpacing(10);

    this->setLayout(rootLayout);
    this->setWindowTitle("Initialize obstacle");

    connect(mCommitButton,SIGNAL(released()),this,SLOT(commitObstacleUpdate()));
}

void ObstacleDialog::commitObstacleUpdate()
{
    mObstacle.x = mCenterXInput->value();
    mObstacle.y = mCenterYInput->value();
    mObstacle.z = mCenterZInput->value();
    mObstacle.radius = mRadiusInput->value();

    emit finished(Accepted);
}

ObstacleItem::ObstacleItem(FlockSimulator::ParameterSimulation::Obstacle &obstacle)
{
    mObstacle = obstacle;

    mCenterXLabel = new QLabel(QString("<b>Center x: </b>")+QString::number(mObstacle.x));
    mCenterYLabel =new QLabel(QString("<b>y: </b>")+QString::number(mObstacle.y));
    mCenterZLabel =new QLabel(QString("<b>z: </b>")+QString::number(mObstacle.radius));
    mRadiusLabel =new QLabel(QString("<b>Radius: </b>")+QString::number(mObstacle.z));

    mDeleteButton = new QPushButton();
    mUpdateButton = new QPushButton();

    QPixmap pixmap(":/resources/icons/delete.png");
    QIcon deleteIcon(pixmap);
    mDeleteButton->setIcon(deleteIcon);
    mDeleteButton->setFixedSize(32,32);
    mDeleteButton->setFlat(true);
    QPixmap p(":/resources/icons/change.png");
    QIcon updadteIcon(p);
    mUpdateButton->setIcon(updadteIcon);
    mUpdateButton->setFixedSize(32,32);
    mUpdateButton->setFlat(true);


    QVBoxLayout* itemLayout = new QVBoxLayout;
    this->setLayout(itemLayout);

    QHBoxLayout* firstLayer = new QHBoxLayout;
    QHBoxLayout* secondLayer = new QHBoxLayout;

    itemLayout->addLayout(firstLayer);
    itemLayout->addLayout(secondLayer);

    firstLayer->addWidget(mRadiusLabel);
    firstLayer->addWidget(mUpdateButton);
    firstLayer->addWidget(mDeleteButton);

    secondLayer->addWidget(mCenterXLabel);
    secondLayer->addWidget(mCenterYLabel);
    secondLayer->addWidget(mCenterZLabel);
}

void ObstacleItem::disableButtons(bool b)
{
    mDeleteButton->setDisabled(b);
    mUpdateButton->setDisabled(b);
}

void ObstacleItem::updateItem(FlockSimulator::ParameterSimulation::Obstacle &obstacle)
{
    mObstacle = obstacle;

    mCenterXLabel->setText(QString("<b>Center x: </b>")+QString::number(mObstacle.x));
    mCenterYLabel->setText(QString("<b>Center y: </b>")+QString::number(mObstacle.y));
    mCenterZLabel->setText(QString("<b>Center z: </b>")+QString::number(mObstacle.radius));
    mRadiusLabel->setText(QString("<b>Radius: </b>")+QString::number(mObstacle.z));
}
