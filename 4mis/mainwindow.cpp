#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSize>
#include <QIcon>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupSignals()
{

    ui->insertFourmiliere->setShortcut(Qt::ALT+Qt::Key_F);
    ui->insertBuisson->setShortcut(Qt::ALT+Qt::Key_B);
    ui->actionAccelerer->setShortcut(Qt::Key_A);
    ui->actionDecelerer->setShortcut(Qt::Key_D);
    ui->actionPause->setShortcut(Qt::Key_P);
    ui->actionNew->setShortcut(Qt::CTRL+Qt::Key_N);

    connect(ui->insertFourmiliere, SIGNAL(triggered(bool)), this, SLOT(onInsertFourmiliereButtonClicked()));
    connect(ui->insertBuisson, SIGNAL(triggered(bool)), this, SLOT(onInsertBuissonButtonClicked()));
    connect(ui->actionAccelerer, SIGNAL(triggered(bool)), this, SLOT(onAccelerateButtonClicked()));
    connect(ui->actionDecelerer, SIGNAL(triggered(bool)), this, SLOT(onDecelerateButtonClicked()));
    connect(ui->actionPause, SIGNAL(triggered(bool)), this, SLOT(onPauseButtonClicked()));
    connect(ui->actionNew, SIGNAL(triggered(bool)), this, SLOT(onNewButtonClicked()));

    connect(ui->insertFourmiliereButton, SIGNAL(pressed()), this, SLOT(onInsertFourmiliereButtonClicked()));
    connect(ui->insertBuissonButton, SIGNAL(pressed()), this, SLOT(onInsertBuissonButtonClicked()));
    connect(ui->accelerateButton, SIGNAL(pressed()), this, SLOT(onAccelerateButtonClicked()));
    connect(ui->decelerateButton, SIGNAL(pressed()), this, SLOT(onDecelerateButtonClicked()));
    connect(ui->pauseButton, SIGNAL(pressed()), this, SLOT(onPauseButtonClicked()));
    connect(ui->newButton, SIGNAL(pressed()), this, SLOT(onNewButtonClicked()));

}

void MainWindow::disableInsertFourmiliere()
{
    ui->insertFourmiliere->setDisabled(true);
    ui->insertFourmiliereButton->setDisabled(true);
}

void MainWindow::disableInsertBuisson()
{
    ui->insertBuisson->setDisabled(true);
    ui->insertBuissonButton->setDisabled(true);
}

void MainWindow::disableAccelerateButton()
{
    ui->actionAccelerer->setDisabled(true);
    ui->accelerateButton->setDisabled(true);
}

void MainWindow::disableDecelerateButton()
{
    ui->actionDecelerer->setDisabled(true);
    ui->decelerateButton->setDisabled(true);
}

void MainWindow::enableAccelerateButton()
{
    ui->actionAccelerer->setDisabled(false);
    ui->accelerateButton->setDisabled(false);
}

void MainWindow::enableDecelerateButton()
{
    ui->actionDecelerer->setDisabled(false);
    ui->decelerateButton->setDisabled(false);
}

void MainWindow::changePauseButton()
{
    if(ui->actionPause->text() == "Pause")
    {
        ui->actionPause->setText("Resume");
        QPixmap pic(":/images/images/resume.png");
        QIcon icon(pic);
        ui->pauseButton->setIcon(icon);
        ui->pauseButton->setIconSize(pic.size());
        ui->pauseButton->setText("Resume");
    }
    else
    {
        ui->actionPause->setText("Pause");
        QPixmap pic(":/images/images/pause.png");
        QIcon icon(pic);
        ui->pauseButton->setIcon(icon);
        ui->pauseButton->setIconSize(pic.size());
        ui->pauseButton->setText("Pause");
    }
}

void MainWindow::onInsertFourmiliereButtonClicked()
{
    emit insertFourmiliereButtonClicked();
}
void MainWindow::onInsertBuissonButtonClicked()
{
    emit insertBuissonButtonClicked();
}
void MainWindow::onAccelerateButtonClicked()
{
    emit accelerateButtonClicked();
}
void MainWindow::onDecelerateButtonClicked()
{
    emit decelerateButtonClicked();
}
void MainWindow::onPauseButtonClicked()
{
    emit pauseButtonClicked();
}
void MainWindow::onNewButtonClicked()
{
    ui->insertFourmiliere->setDisabled(false);
    ui->insertFourmiliereButton->setDisabled(false);
    ui->insertBuisson->setDisabled(false);
    ui->insertBuissonButton->setDisabled(false);
    emit newButtonClicked();
}

void MainWindow::setupScene(QGraphicsScene* actu)
{
    ui->graphicsView->setScene(actu);
}

