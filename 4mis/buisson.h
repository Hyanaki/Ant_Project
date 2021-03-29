#ifndef BUISSON_H
#define BUISSON_H

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

class Buisson : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Buisson(QVector2D &pos, Actualisation* actu, int nbfood, QGraphicsItem *parent = Q_NULLPTR);
    void decrementFood();

    int rayon() const;

    virtual QRectF boundingRect() const override;
    virtual bool contains(const QPointF &point) const override;
    virtual bool isObscuredBy(const QGraphicsItem *item) const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) override;
    virtual QPainterPath shape() const override;
    virtual int type() const override;

signals:

public slots:

private:
    Actualisation* m_actu;
    int m_rayon;
    int m_nbfood;
};

#endif // BUISSON_H
