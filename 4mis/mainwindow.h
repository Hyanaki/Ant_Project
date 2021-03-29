#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setupSignals();
    void setupScene(QGraphicsScene* scene);
    void disableAccelerateButton();
    void disableDecelerateButton();
    void enableAccelerateButton();
    void enableDecelerateButton();
    void changePauseButton();

    void disableInsertBuisson();
    void disableInsertFourmiliere();

private slots:
    void onInsertFourmiliereButtonClicked();
    void onInsertBuissonButtonClicked();
    void onAccelerateButtonClicked();
    void onDecelerateButtonClicked();
    void onPauseButtonClicked();
    void onNewButtonClicked();

signals:
    void insertFourmiliereButtonClicked();
    void insertBuissonButtonClicked();
    void accelerateButtonClicked();
    void decelerateButtonClicked();
    void pauseButtonClicked();
    void newButtonClicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
