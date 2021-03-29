#include "fourmiliere.h"
#include "ouvriere.h".h"
#include "actualisation.h"
#include <QPainter>
#include <QDebug>

Fourmiliere::Fourmiliere(QVector2D &pos, Actualisation* actu, QGraphicsItem* parent) :
    QGraphicsItem(parent),
    m_actu(actu),
    m_nbfood(0),
    m_rayon(10),
    m_fourmicreated(false)
{
    this->setPos(pos.x(),pos.y());
}

void Fourmiliere::advance(int phase)
{
    if(phase == 1)
    {
        if(m_nbfood >= 500)
        {
            m_nbfood -= 500;
            this->m_actu->createReine(this);
        }
        if(m_lifourmis.count() <= 20)
        {
            if(m_nbfood % 5 == 0 && !m_fourmicreated)
            {
                createFourmi();
                m_fourmicreated = true;
            }
            else if(m_nbfood % 5 == 1)
            {
                m_fourmicreated = false;
            }
        }
    }
}

int Fourmiliere::rayon() const
{
    return m_rayon;
}

void Fourmiliere::createFourmi()
{
    Ouvriere * pt = new Ouvriere(m_actu, this);
    m_lifourmis.append(pt);
    m_actu->addItem(pt);
}

void Fourmiliere::deleteFourmi(Fourmi* fourmi)
{
    m_actu->removeItem(fourmi);
    int it = this->m_lifourmis.indexOf(fourmi);
    m_lifourmis.removeAt(it);
}

void Fourmiliere::incrementFood()
{
    this->m_nbfood++;
}

void Fourmiliere::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::gray);
    painter->drawRect(-m_rayon, -m_rayon, 2*m_rayon, 2*m_rayon);
}

QPainterPath Fourmiliere::shape() const
{
    QPainterPath path;
    path.addRect(-m_rayon, -m_rayon, 2*m_rayon, 2*m_rayon);
    return path;
}

QRectF Fourmiliere::boundingRect() const
{
    qreal adjust = 0.5;
    return QRectF(-m_rayon-adjust, -m_rayon-adjust, 2*m_rayon+adjust, 2*m_rayon+adjust);
}

int Fourmiliere::type() const
{
    return 102;
}

bool Fourmiliere::contains(const QPointF &point) const {return NULL;}
bool Fourmiliere::isObscuredBy(const QGraphicsItem *item) const {return NULL;}

