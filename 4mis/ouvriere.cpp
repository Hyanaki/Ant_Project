#include "ouvriere.h"
#include <math.h>
#include <QDebug>
#include <QRectF>
#include <QMutex>

#include "actualisation.h"
#include "buisson.h"
#include "pheromone.h"

Ouvriere::Ouvriere(Actualisation* actu, Fourmiliere* maison, QGraphicsItem *parent) :
    Fourmi(actu,10, parent),
    m_cycle(5000),
    m_haveFood(false),
    m_onpheromone(NULL),
    m_maison(maison)
{
    setPos(m_maison->x(),m_maison->y());
}

bool Ouvriere::collisionFourmiliere()
{
    float rayon = m_maison->rayon();
    float posX = abs(this->m_maison->x()- x());
    float posY = abs(this->m_maison->y()- y());

    return posX < rayon && posY < rayon;
}

void Ouvriere::retour()
{
    float posX = x();
    float posY = y();

    float dx = abs(posX - this->m_maison->x());
    float dy = abs(posY - this->m_maison->y());
    m_direction = atan(dy/dx);
    if(this->m_maison->x() < x())
        m_direction = 3.14159 - m_direction;
    if(this->m_maison->y() > y())
        m_direction = - m_direction;

    this->setPos(posX+cos(m_direction),posY-sin(m_direction));
    m_actu->createPheromone(this);
}

void Ouvriere::advance(int phase)
{
    if(phase==1)
    {
        if(m_haveFood)
        {
            retour();
            if(collisionFourmiliere())
            {
                m_direction = m_direction + 3.14159;
                m_onpheromone = NULL;
                m_haveFood = false;
                this->m_maison->incrementFood();
            }
        }
        else{
            Buisson* buisson = this->m_actu->collisionBuisson(this);
            if(NULL != buisson)
            {
                m_haveFood = true;
                buisson->decrementFood();

            }
            else
            {
                // Sur un pheromone ?
                Pheromone* pheromone = m_actu->collisionPheromone(this,false);

                // Actuellement sur aucune pheromone
                if(NULL == m_onpheromone)
                {
                    if(NULL != pheromone)
                    {
                        followPheromone(pheromone);
                        /*float dx = abs(x()- (*pheromone).x());
                        float dy = abs(y() - (*pheromone).y());

                        if(dx != 0 && dy != 0)
                        {
                            float angle = atan(dy/dx);
                            if((*pheromone).x() < x())
                                angle = 3.14159 - angle;
                            if((*pheromone).y() > y())
                                angle = - angle;

                            m_direction = angle;

                            m_onpheromone = pheromone;
                        }
                        else m_onpheromone = NULL;
*/
                    }
                    else{
                        move();
                    }
                }
                // Change de pheromone
                else if(NULL != pheromone && (*m_onpheromone).pos() != (*pheromone).pos())
                {
                    followPheromone(pheromone);
                    /*float dx = abs(x()- (*pheromone).x());
                    float dy = abs(y() - (*pheromone).y());

                    if(dx != 0 && dy != 0)
                    {
                        float angle = atan(dy/dx);
                        if((*pheromone).x() < x())
                            angle = 3.14159 - angle;
                        if((*pheromone).y() > y())
                            angle = - angle;

                        if(angle <= m_direction+1.04797
                                && angle >= m_direction-1.04797) // pi/3
                            m_direction = angle;

                        m_onpheromone = pheromone;
                    }*/
                }
                else
                {
                    move();
                }
            }
        }
        this->m_cycle--;
        if(m_cycle == 0)
        {
            m_maison->deleteFourmi(this);
            delete this;
        }
    }
}

void Ouvriere::followPheromone(Pheromone* pheromone)
{
    float first_direction = m_direction;
    float dx = abs(x()- (*pheromone).x());
    float dy = abs(y() - (*pheromone).y());

    if(dx != 0 && dy != 0)
    {
        float angle = atan(dy/dx);
        if((*pheromone).x() < x())
            angle = 3.14159 - angle;
        if((*pheromone).y() > y())
            angle = - angle;

        if(angle <= m_direction+1.57079
                && angle >= m_direction-1.57079) // 1.04797 pi/3
            m_direction = (angle + first_direction)/2;

        m_onpheromone = pheromone;
    }
    collidingFourmis();

    this->setPos(x()+cos(m_direction),y()-sin(m_direction));
}

void Ouvriere::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::blue);
    painter->drawEllipse(-m_rayon/2, -m_rayon/2, m_rayon, m_rayon);

    if(m_haveFood)
    {
        painter->setBrush(Qt::red);
        painter->drawEllipse(-4,-4,8,8);
    }
}
