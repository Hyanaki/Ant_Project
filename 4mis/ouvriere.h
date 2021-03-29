#ifndef OUVRIERE_H
#define OUVRIERE_H

#include <QObject>
#include "fourmi.h"
#include "fourmiliere.h"
#include "pheromone.h"

class Ouvriere: public Fourmi
{
    Q_OBJECT
public:
    Ouvriere(Actualisation* actu, Fourmiliere* maison, QGraphicsItem *parent = Q_NULLPTR);
    void retour();
    bool collisionFourmiliere();
    virtual void advance(int phase) override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) override;

    void followPheromone(Pheromone* pheromone);

signals:

private slots:

private:
    int m_cycle;
    bool m_haveFood;
    Pheromone* m_onpheromone;
    Fourmiliere* m_maison;
};

#endif // OUVRIERE_H
