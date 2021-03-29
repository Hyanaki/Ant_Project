#ifndef ACTUALISATION_H
#define ACTUALISATION_H

#include <QObject>
#include <QList>
#include <QGraphicsScene>
#include <QTimer>
#include "pheromone.fwd.h"
#include "fourmiliere.fwd.h"
#include "buisson.fwd.h"
#include "fourmi.fwd.h"
#include "mainwindow.h"

class Actualisation :  public QGraphicsScene
{
    Q_OBJECT
public:
    Buisson* collisionBuisson(Fourmi * const fourmi);
    Pheromone* collisionPheromone(Fourmi* fourmi, bool haveFood);
    void createPheromone(Fourmi* fourmi);
    void createReine(Fourmiliere* Fourmiliere);
    void createFourmiliere(QVector2D &pos);
    bool onAreaToCreateFourmiliere(Fourmi * fourmi);


    explicit Actualisation(MainWindow* window, QTimer* timer);
    void setupSignals();
    void initialize();

    void addRemovedPheromones(Pheromone* phe);

signals:

public slots:
    void onInsertFourmiliereButtonClicked();
    void onInsertBuissonButtonClicked();
    void onAccelerateButtonClicked();
    void onDecelerateButtonClicked();
    void onPauseButtonClicked();
    void onDisableBuissonButton();
    void onDisableFourmiliereButton();

    //void clearRemovedPheromones();

private:
    QList<Buisson*> m_libuisson;
    QList<Fourmiliere*> m_lifourmilieres;
    QList<Pheromone*> m_liremovedpheromones;
    int m_compteurclear;

    MainWindow* m_window;
    QTimer* m_timer;

};

#endif // ACTUALISATION_H
