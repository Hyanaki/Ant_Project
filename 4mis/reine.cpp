#include "reine.h"
#include "actualisation.h"

Reine::Reine(Actualisation* actu, QVector2D pos, QGraphicsItem* parent) :
    Fourmi(actu,20, parent),
    m_posinit(pos)
{
    setPos(pos.x(),pos.y());
}

void Reine::advance(int phase)
{
    if(phase==1)
    {
        move();
    }
    QVector2D pos(x(),y());
    if(m_actu->onAreaToCreateFourmiliere(this))
    {
        m_actu->createFourmiliere(pos);
        m_actu->removeItem(this);
        delete this;
    }
}

void Reine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::cyan);
    painter->drawEllipse(-m_rayon/2, -m_rayon/2, m_rayon, m_rayon);
}
