#ifndef PHEROMONE_H
#define PHEROMONE_H

#include "actualisation.fwd.h"
#include <QObject>
#include <QGraphicsItem>

#include <QRectF>
#include <QPainterPath>
#include <QPointF>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QWidget>

class Pheromone : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Pheromone(QVector2D &pos, Actualisation* actu, QGraphicsItem *parent = Q_NULLPTR);
    void actualizeCycle();
    int rayon() const;

    virtual void advance(int phase) override;

    virtual QRectF boundingRect() const override;
    virtual bool contains(const QPointF &point) const override;
    virtual bool isObscuredBy(const QGraphicsItem *item) const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) override;
    virtual QPainterPath shape() const override;
    virtual int type() const override;

private:
    Actualisation* m_actu;
    int m_cycle;
    int m_rayon;
    int m_compteurtimer;
};

#endif // PHEROMONE_H
