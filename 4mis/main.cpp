#include "mainwindow.h"
#include <QApplication>
#include <QTimer>
#include <QLabel>
#include <QPixmap>
#include "actualisation.h"
#include "buisson.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /*QLabel label;
        //on donne l'image au label
    QPixmap pix ;
    pix.load("119_nilitsu",NULL,Qt::ImageConversionFlags(32));
        label.setPixmap(pix);
        label.show();*/

    MainWindow w;
    QTimer* timer = new QTimer();
    Actualisation controller( &w, timer);
    w.setupScene(&controller);

    /*Buisson* buiss1 = new Buisson(&controller, 1000);
    buiss1->setPos(-15,15);
    controller.addItem(buiss1);
    Buisson* buiss2 = new Buisson(&controller, 1000);
    buiss2->setPos(0,-15);
    controller.addItem(buiss2);
    Buisson* buiss = new Buisson(&controller, 1000);
    buiss->setPos(15,15);
    controller.addItem(buiss);*/

    controller.initialize();

    return a.exec();
}
