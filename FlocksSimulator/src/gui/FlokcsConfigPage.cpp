#include "FlocksConfigPage.h"

FlocksConfigPage::FlocksConfigPage()
    : AbstractPage(FLOCKS_CONFIG)
{
    mAddFlocksButton = new QPushButton();
    mPredationBox = new QCheckBox("Predation");

    QPixmap pixmap(":/resources/icons/add.png");
    QIcon buttonIcon(pixmap);
    mAddFlocksButton->setIcon(buttonIcon);

    mAddFlocksButton->setFixedSize(QSize(32,32));
    mAddFlocksButton->setFlat(true);

    QVBoxLayout* rootLayout = new QVBoxLayout;

    QHBoxLayout*  headerLayoutFlock= new QHBoxLayout;

    headerLayoutFlock->addWidget(new QLabel("<h3>Flocks </h3>"));
    headerLayoutFlock->addWidget(mPredationBox,Qt::AlignLeft);
    headerLayoutFlock->addWidget(mAddFlocksButton);

    mFlocksListLayout = new QVBoxLayout;

    FlockSimulator::ParameterSimulation::Flock flockDefault;
    addFlockItem(flockDefault);

    QWidget* headerWidget = new QWidget();
    headerWidget->setObjectName("headerWidget");
    headerWidget->setLayout(headerLayoutFlock);
    headerWidget->setStyleSheet("QWidget#headerWidget{"
                                " border-bottom: 1px solid grey;"
                                "}");
    QWidget* listWidget = new QWidget();
    listWidget->setLayout(mFlocksListLayout);

    rootLayout->addWidget(headerWidget);
    rootLayout->addWidget(listWidget);



    QWidget* rootWidget = new QWidget();
    rootWidget->setLayout(rootLayout);
    rootWidget->setObjectName("flocksRootWidget");
    rootWidget->setStyleSheet("#flocksRootWidget{border: 1px solid grey;}");
    rootLayout->setContentsMargins(0,0,0,0);
    QHBoxLayout* layout = new QHBoxLayout();
    layout->addWidget(rootWidget);

    this->setTitle("Setting flocks");
    this->setLayout(layout);
    connect(mAddFlocksButton,SIGNAL(released()),this,SLOT(showFlockDialog()));

}

void FlocksConfigPage::setParameterSimulation(FlockSimulator::ParameterSimulation &parameter, QVector<FlockSimulator::ParameterSimulation> &pVector)
{
    if(!mViewed) return;

    parameter.setPredation(mPredationBox->isChecked());
    qDebug() <<"FlocksPage";
    parameter.clearFlocks();
    foreach (FlockItem* item, mFlockItems) {
        FlockSimulator::ParameterSimulation::Flock flock = item->getFlock();
        parameter.addFlock(flock);
    }

    //Add predation
}

void FlocksConfigPage::addFlockItem(FlockSimulator::ParameterSimulation::Flock &flock)
{

    FlockItem* item = new FlockItem(flock);
    mFlockItems.append(item);
    mFlocksListLayout->addWidget(item);
    connect(item->mUpdateButton,SIGNAL(released()),this,SLOT(showFlockDialog()));
    connect(item->mDeleteButton,SIGNAL(released()),this,SLOT(deleteFlockItem()));

    if(mFlockItems.length()> 1){
        mFlockItems.first()->mDeleteButton->setDisabled(false);
    }else{
        mFlockItems.first()->mDeleteButton->setDisabled(true);
    }

    if(mFlockItems.length()==4)
        mAddFlocksButton->setDisabled(true);
    else
        mAddFlocksButton->setDisabled(false);
}

void FlocksConfigPage::showFlockDialog()
{

    mAddFlocksButton->setDisabled(true);
    foreach(FlockItem* item, mFlockItems)
        item->disableButtons(true);

    mLastDialogCaller = QObject::sender();

    if(mLastDialogCaller == mAddFlocksButton){
        FlockSimulator::ParameterSimulation::Flock flock;
        mFlockDialog=new FlockDialog(flock);
    }else{
        FlockItem* item = (FlockItem*)mLastDialogCaller->parent();
        FlockSimulator::ParameterSimulation::Flock flock = item->getFlock();
        mFlockDialog=new FlockDialog(flock);
    }
    connect(mFlockDialog,SIGNAL(finished(int)),this, SLOT(closeFlockDialog(int)));
    mFlockDialog->show();
}

void FlocksConfigPage::closeFlockDialog(int result)
{
    if(result == QDialog::Rejected){

    }else{

        if(mLastDialogCaller == mAddFlocksButton){
            FlockSimulator::ParameterSimulation::Flock flock = mFlockDialog->getFlock();
            addFlockItem(flock);
        }else{
            FlockItem* item = (FlockItem*)mLastDialogCaller->parent();
            FlockSimulator::ParameterSimulation::Flock flock = mFlockDialog->getFlock();
            item->updateItem(flock);
        }

    }
    if(mFlockItems.length()<4)
        mAddFlocksButton->setDisabled(false);

    foreach(FlockItem* item, mFlockItems)
        item->disableButtons(false);

    delete mFlockDialog;
    mLastDialogCaller = nullptr;
    mFlockDialog = nullptr;
}

void FlocksConfigPage::deleteFlockItem()
{
    QObject* obj = QObject::sender();
    FlockItem* item = (FlockItem *)obj->parent();

    mFlockItems.removeOne(item);
    mFlocksListLayout->removeWidget(item);
    delete item;

    if(mFlockItems.length()== 1){
        mFlockItems.first()->mDeleteButton->setDisabled(true);
    }else if(mFlockItems.length()<4)
        mAddFlocksButton->setDisabled(false);
}

FlockDialog::FlockDialog(FlockSimulator::ParameterSimulation::Flock &flock)
    :QDialog(nullptr)
{
    mFlockLabel = new QLabel();
    mBoidsNumInput = new QSpinBox;
    mBoidsSpecieInput = new QSpinBox;
    mMinXInput = new QDoubleSpinBox;
    mMaxXInput = new QDoubleSpinBox;
    mMinZInput = new QDoubleSpinBox;
    mMaxZInput = new QDoubleSpinBox;
    mCommitButton = new QPushButton("Ok");

    mFlock = flock;

    mBoidsNumInput->setValue(mFlock.numBoids);
    mBoidsSpecieInput->setValue(mFlock.specie);
    mMinXInput->setValue(mFlock.xMin);
    mMaxXInput->setValue(mFlock.xMax);
    mMinZInput->setValue(mFlock.zMin);
    mMaxZInput->setValue(mFlock.zMax);

    QVBoxLayout* rootLayout = new QVBoxLayout;

    QHBoxLayout* headerLayout = new QHBoxLayout;
    headerLayout->addWidget(new QLabel("Flock"));
    headerLayout->addWidget(mFlockLabel);
    QHBoxLayout* centralLayout = new QHBoxLayout;

    QFormLayout* formLayoutR = new QFormLayout;
    QFormLayout* formLayoutL = new QFormLayout;


    formLayoutL->addRow(new QLabel("Boids number"),mBoidsNumInput);
    formLayoutR->addRow(new QLabel("Boids specie"),mBoidsSpecieInput);
    formLayoutL->addRow(new QLabel("Min X"),mMinXInput);
    formLayoutR->addRow(new QLabel("Max X"),mMaxXInput);
    formLayoutL->addRow(new QLabel("Min Z"),mMinZInput);
    formLayoutR->addRow(new QLabel("Max Z"),mMaxZInput);

    centralLayout->addLayout(formLayoutL);
    centralLayout->addLayout(formLayoutR);

    rootLayout->addLayout(headerLayout);
    rootLayout->addLayout(centralLayout);

    rootLayout->addWidget(mCommitButton);

    rootLayout->setSpacing(10);


    this->setLayout(rootLayout);
    this->setWindowTitle("Initialize flock");

    connect(mCommitButton,SIGNAL(released()),this,SLOT(commitFlockUpdate()));
}

void FlockDialog::commitFlockUpdate()
{
    mFlock.numBoids = mBoidsNumInput->value();
    mFlock.xMin = mMinXInput->value();
    mFlock.xMax = mMaxXInput->value();
    mFlock.zMin = mMinZInput->value();
    mFlock.zMax = mMaxZInput->value();
    mFlock.specie = mBoidsSpecieInput->value();

    emit finished(Accepted);
}


FlockItem::FlockItem( FlockSimulator::ParameterSimulation::Flock &flock)
    :QWidget(nullptr)
{

    mFlock = flock;

    mNumBoidLabel = new QLabel(QString("Num Boid: ")+QString::number(mFlock.numBoids));
    mSpecieLabel = new QLabel(QString("Specie: ")+QString::number(mFlock.specie));
    mMinXLabel = new QLabel(QString("Min X: ")+QString::number(mFlock.zMin));
    mMaxXLabel =new QLabel(QString("Max X: ")+QString::number(mFlock.xMax));
    mMinZLabel =new QLabel(QString("Min Z: ")+QString::number(mFlock.zMin));
    mMaxZLabel =new QLabel(QString("Max Z: ")+QString::number(mFlock.zMax));

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

    //    firstLayer->addWidget(new QLabel("Flock"));


    firstLayer->addWidget(mNumBoidLabel);
    firstLayer->addWidget(mSpecieLabel);
    firstLayer->addWidget(mUpdateButton);
    firstLayer->addWidget(mDeleteButton);

    secondLayer->addWidget(mMinXLabel);
    secondLayer->addWidget(mMaxXLabel);

    secondLayer->addWidget(mMinZLabel);
    secondLayer->addWidget(mMaxZLabel);
}

void FlockItem::disableButtons(bool b)
{
    mDeleteButton->setDisabled(b);
    mUpdateButton->setDisabled(b);
}
void FlockItem::updateItem(FlockSimulator::ParameterSimulation::Flock &flock)
{
    mFlock = flock;

    mNumBoidLabel->setText(QString("Num Boid: ")+QString::number(mFlock.numBoids));
    mSpecieLabel->setText(QString("Specie: ")+QString::number(mFlock.specie));
    mMinXLabel->setText(QString("Min X: ")+QString::number(mFlock.zMin));
    mMaxXLabel->setText(QString("Max X: ")+QString::number(mFlock.xMax));
    mMinZLabel->setText(QString("Min Z: ")+QString::number(mFlock.zMin));
    mMaxZLabel->setText( QString("Max Z: ")+QString::number(mFlock.zMax));
}
