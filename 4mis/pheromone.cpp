#include "pheromone.h"
#include "actualisation.h"
#include <QThread>
#include <QDebug>

Pheromone::Pheromone(QVector2D &pos, Actualisation* actu, QGraphicsItem *parent) :
    QGraphicsItem(parent),
    m_actu(actu),
    m_rayon(8),
    m_cycle(255),
    m_compteurtimer(0)
{
    setPos((int)pos.x(),(int)pos.y());
}

int Pheromone::rayon() const
{
    return m_rayon;
}

void Pheromone::actualizeCycle()
{
    m_cycle = 255;
}

void Pheromone::advance(int phase)
{
    if(phase ==1)
    {
        m_compteurtimer++;
        if(m_compteurtimer >= 3)
        {
            if(m_cycle >= 0) m_cycle--;
            if(m_cycle == 0)
            {
                m_actu->removeItem(this);
                m_actu->addRemovedPheromones(this);
            }
            m_compteurtimer=0;
        }
    }
}

void Pheromone::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QColor color(255,0,0,255*((float)m_cycle/500));
    painter->setBrush(color);
    painter->drawEllipse(-m_rayon, -m_rayon, 2*m_rayon, 2*m_rayon);
}

QPainterPath Pheromone::shape() const
{
    QPainterPath path;
    path.addRect(-m_rayon,-m_rayon,2*m_rayon,2*m_rayon);
    return path;
}

QRectF Pheromone::boundingRect() const
{
    qreal adjust = 0.5;
    return QRectF(-m_rayon-adjust,-m_rayon-adjust,2*m_rayon+adjust,2*m_rayon+adjust);
}

int Pheromone::type() const
{
    return 100;
}

bool Pheromone::contains(const QPointF &point) const {return NULL;}
bool Pheromone::isObscuredBy(const QGraphicsItem *item) const {return NULL;}
