#ifndef REINE_H
#define REINE_H

#include <QObject>
#include "fourmi.h"

class Reine : public Fourmi
{
    Q_OBJECT
public:
    Reine(Actualisation* actu, QVector2D pos, QGraphicsItem *parent = Q_NULLPTR);
    virtual void advance(int phase) override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) override;

signals:

private:
    QVector2D m_posinit;

};

#endif // REINE_H
