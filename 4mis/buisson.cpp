#include "buisson.h"
#include "actualisation.h"
#include <QDebug>

Buisson::Buisson(QVector2D &pos, Actualisation* actu, int nbfood, QGraphicsItem *parent) :
    QGraphicsItem(parent),
    m_actu(actu),
    m_nbfood(nbfood),
    m_rayon(nbfood/10)
{
    this->setPos(pos.x(),pos.y());
}

int Buisson::rayon() const
{
    return m_rayon;
}

void Buisson::decrementFood()
{
    m_nbfood--;
    m_rayon = m_nbfood/10;
    if(m_nbfood == 0)
    {
        m_actu->removeItem(this);
    }
}

void Buisson::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::green);
    painter->drawEllipse(-m_rayon,-m_rayon,2*m_rayon,2*m_rayon);
}

QPainterPath Buisson::shape() const
{
    QPainterPath path;
    path.addRect(-m_rayon,-m_rayon,2*m_rayon,2*m_rayon);
    return path;
}

QRectF Buisson::boundingRect() const
{
    qreal adjust = 0.5;
    return QRectF(-m_rayon-adjust,-m_rayon-adjust,2*m_rayon+adjust,2*m_rayon+adjust);
}

int Buisson::type() const
{
    return 103;
}

bool Buisson::contains(const QPointF &point) const {return NULL;}
bool Buisson::isObscuredBy(const QGraphicsItem *item) const {return NULL;}
