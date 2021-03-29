#ifndef FOURMI_H
#define FOURMI_H

#include <QObject>
#include <QGraphicsItem>
#include <QVector2D>
#include "actualisation.fwd.h"

#include <QRectF>
#include <QPainterPath>
#include <QPointF>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QWidget>

class Fourmi : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Fourmi(Actualisation* actu,int rayon, QGraphicsItem *parent = Q_NULLPTR);
    void move();
    void collidingFourmis();

    int rayon() const;


    virtual QRectF boundingRect() const override;
    virtual QPainterPath shape() const override;
    virtual int type() const override;

signals:

protected:
    Actualisation* m_actu;
    float m_direction;
    int m_rayon;
};

#endif // FOURMI_H
