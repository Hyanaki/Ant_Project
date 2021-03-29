#ifndef FOURMILIERE_H
#define FOURMILIERE_H

#include <QObject>
#include <QVector2D>
#include <QGraphicsItem>
#include "fourmi.fwd.h"
#include "actualisation.fwd.h"

#include <QRectF>
#include <QPainterPath>
#include <QPointF>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QWidget>

class Fourmiliere : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Fourmiliere(QVector2D &pos, Actualisation* actu, QGraphicsItem *parent = Q_NULLPTR);
    void incrementFood();
    void createFourmi();
    void deleteFourmi(Fourmi* fourmi);
    int rayon() const;

    virtual void advance(int phase) override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    virtual QRectF boundingRect() const override;
    virtual bool contains(const QPointF &point) const override;
    virtual bool isObscuredBy(const QGraphicsItem *item) const override;
    virtual QPainterPath shape() const override;
    virtual int type() const override;

signals:

public slots:

private:
    Actualisation* m_actu;
    QList<Fourmi *> m_lifourmis;
    int m_nbfood;
    int m_rayon;
    bool m_fourmicreated;
};

#endif // FOURMILIERE_H
