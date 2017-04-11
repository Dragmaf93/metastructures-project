#include "gui/MainWindow.h"
#include "SimulatorsManager.h"
#include"DatabaseLogger.h"

#include <QApplication>
#include <QScreen>
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;

    QRect screen = QApplication::primaryScreen()->geometry();
    w.resize(screen.width()*0.3,screen.height()/2);

    w.setWindowTitle("Flocks Simulator");
    w.show();

    return a.exec();
}
