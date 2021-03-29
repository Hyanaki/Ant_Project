#include "fourmi.h"
#include "fourmiliere.h"
#include "actualisation.h"
#include <QDebug>
#include "pheromone.h"

Fourmi::Fourmi(Actualisation* actu,int rayon, QGraphicsItem *parent) :
    QGraphicsItem(parent),
    m_actu(actu),
    m_rayon(rayon),
    m_direction(NULL)
{

}

int Fourmi::rayon() const
{
    return m_rayon;
}

void Fourmi::collidingFourmis()
{
    QPolygonF polygon;
    polygon.append(mapToScene(boundingRect()));
    QList<QGraphicsItem *> litem = scene()->items(polygon,Qt::IntersectsItemBoundingRect);

    foreach (QGraphicsItem *item, litem) {
        if (item == this || item->type() != 101)
            continue;

        m_direction = 3.14159 - m_direction;
        //qDebug() << rand()%100 << "bam";
    }
}

void Fourmi::move()
{
    float random = (float)(rand()%100)/100;
    if(NULL == m_direction)
    {
        m_direction = (random * 360) * 3.14159/180;
    }
    else
    {
        float randomangle = (float)(rand()%100)/100;
        m_direction = random <=0.5 ? m_direction - (randomangle *20) * 3.14159/180
                : m_direction + (randomangle *20) * 3.14159/180;
    }
    collidingFourmis();

    // Si en dehors de la scene, retour vers l'interieur
    if(abs(x()) > 420 || abs(y()) > 270)
    {
        float dx = abs(x() - m_actu->sceneRect().center().x());
        float dy = abs(y() - m_actu->sceneRect().center().y());
        m_direction = atan(dy/dx);
        if(m_actu->sceneRect().center().x() < x())
            m_direction = 3.14159 - m_direction;
        if(m_actu->sceneRect().center().y() > y())
            m_direction = - m_direction;
    }

    this->setPos(x()+cos(m_direction),y()-sin(m_direction));
}

QRectF Fourmi::boundingRect() const
{
    qreal adjust = 0.5;
    return QRectF(-m_rayon/2-adjust,-m_rayon/2-adjust,m_rayon+adjust,m_rayon+adjust);
}

QPainterPath Fourmi::shape() const
{
    QPainterPath path;
    path.addRect(-m_rayon/2,-m_rayon/2,m_rayon,m_rayon);
    return path;
}

int Fourmi::type() const {
    return 101; // Numéro pour une fourmi
}
