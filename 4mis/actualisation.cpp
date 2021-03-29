#include "actualisation.h"
#include "pheromone.h"
#include "fourmiliere.h"
#include "buisson.h"
#include "reine.h"
#include "fourmi.h"
#include "mainwindow.h"
#include <QDebug>
#include <QGraphicsItem>
#include <QMutex>


Actualisation::Actualisation(MainWindow* window, QTimer* timer):
    m_window(window),
    m_timer(timer),
    m_compteurclear(0)
{
    Q_ASSERT(nullptr != window);
    setItemIndexMethod(QGraphicsScene::NoIndex);
    setSceneRect(-400,-250,800,500);
}

void Actualisation::setupSignals()
{
    this->connect(m_window, SIGNAL(insertFourmiliereButtonClicked()), this, SLOT(onInsertFourmiliereButtonClicked()));
    this->connect(m_window, SIGNAL(insertFourmiliereButtonClicked()), this, SLOT(onDisableFourmiliereButton()));
    this->connect(m_window, SIGNAL(insertBuissonButtonClicked()), this, SLOT(onInsertBuissonButtonClicked()));
    this->connect(m_window, SIGNAL(insertBuissonButtonClicked()), this, SLOT(onDisableBuissonButton()));
    this->connect(m_window, SIGNAL(accelerateButtonClicked()), this, SLOT(onAccelerateButtonClicked()));
    this->connect(m_window, SIGNAL(decelerateButtonClicked()), this, SLOT(onDecelerateButtonClicked()));
    this->connect(m_window, SIGNAL(pauseButtonClicked()), this, SLOT(onPauseButtonClicked()));
    this->connect(m_window, SIGNAL(newButtonClicked()), this, SLOT(clear()));
    m_timer->start(16);
    this->connect(m_timer,SIGNAL(timeout()), this, SLOT(advance()));
    //this->connect(m_timer,SIGNAL(timeout()), this, SLOT(clearRemovedPheromones()));
}

/*void Actualisation::clearRemovedPheromones()
{
    m_compteurclear ++;
    if(m_compteurclear == 100)
    {
        Pheromone* phe = (*m_liremovedpheromones.begin());
        qDebug() << phe->rayon();
       // m_liremovedpheromones.erase(m_liremovedpheromones.begin(),m_liremovedpheromones.end());
        for (auto it=m_liremovedpheromones.begin(); it<m_liremovedpheromones.end();it++ ) {
            m_liremovedpheromones.erase(it);
            delete (*it);
        }
        //qDebug() << phe->rayon();
        m_compteurclear = 0;
    }
}*/


void Actualisation::onDisableBuissonButton()
{
    if(m_libuisson.count() > 60)
    {
        m_window->disableInsertBuisson();
    }
}

void Actualisation::onDisableFourmiliereButton()
{
    if(m_lifourmilieres.count() > 5)
    {
        m_window->disableInsertFourmiliere();
    }
}

void Actualisation::initialize()
{
    m_window->setupSignals();
    this->setupSignals();
    m_window->setupScene(this);

    m_window->show();
}


void Actualisation::onInsertFourmiliereButtonClicked()
{
    QVector2D pos(0.0,0.0);
    Fourmiliere* fourmiliere = new Fourmiliere(pos,this);

    bool posOk = false;

    while(!posOk)
    {
        posOk = true;
        int signe1 = (float)(rand()%100)/100 >= 0.5 ? 1 : -1;
        int signe2 = (float)(rand()%100)/100 >= 0.5 ? 1 : -1;
        int val = rand()%400;
        int val2 = rand()%250;

        fourmiliere->setX(signe1 * val);
        fourmiliere->setY(signe2 * val2);

        for(auto it = m_lifourmilieres.begin();it<m_lifourmilieres.end();it++)
        {
            if(sqrt(pow(fourmiliere->x() - (*it)->x(),2) + pow(fourmiliere->y() - (*it)->y(),2)) < fourmiliere->rayon()*3 + (*it)->rayon()*3)
            {
                posOk = false;
                break;
            }
            posOk = true;
        }
        if(posOk)
        {
            for(auto it = m_libuisson.begin();it<m_libuisson.end();it++)
            {
                if(sqrt(pow(fourmiliere->x() - (*it)->x(),2) + pow(fourmiliere->y() - (*it)->y(),2)) < 2*fourmiliere->rayon() + 2*(*it)->rayon())
                {
                    posOk = false;
                    break;
                }
                posOk = true;
            }
        }
    }

    this->addItem(fourmiliere);
    m_lifourmilieres.push_back(fourmiliere);

    /*QPolygonF polygon;
    QList<QGraphicsItem *> litem;

    while(!posOk)
    {
        polygon.clear();
        polygon.append(fourmiliere->mapToScene(fourmiliere->boundingRect()));
        litem = items(polygon,Qt::IntersectsItemBoundingRect);

        int signe1 = (float)(rand()%100)/100 >= 0.5 ? 1 : -1;
        int signe2 = (float)(rand()%100)/100 >= 0.5 ? 1 : -1;
        int val = rand()%400;
        int val2 = rand()%200;

        fourmiliere->setX(signe1 * val);
        fourmiliere->setY(signe2 * val2);

        cpt = 0;
        foreach (QGraphicsItem *item, litem) {
            if (item->type() == 103 || item->type() == 102)
            {
                cpt++;
                continue;
            }
        }
        if(cpt==0) posOk =true;
    }

    m_lifourmilieres.append(fourmiliere);
    this->addItem(fourmiliere);*/
}

void Actualisation::onInsertBuissonButtonClicked()
{
    bool posOk = false;

    /*QPolygonF polygon;
    QList<QGraphicsItem *> litem;*/
    QVector2D pos(0.0,0.0);
    Buisson* buisson;

    for(int i=0;i<20;i++)
    {
        buisson = new Buisson(pos,this,(rand()%2+1) * 100);
        posOk = false;
        while(!posOk)
        {
            posOk = true;
            int signe1 = (float)(rand()%100)/100 >= 0.5 ? 1 : -1;
            int signe2 = (float)(rand()%100)/100 >= 0.5 ? 1 : -1;
            int val = rand()%400;
            int val2 = rand()%250;

            buisson->setX(signe1 * val);
            buisson->setY(signe2 * val2);

            for(auto it = m_lifourmilieres.begin();it<m_lifourmilieres.end();it++)
            {
                if(sqrt(pow(buisson->x() - (*it)->x(),2) + pow(buisson->y() - (*it)->y(),2)) < 2*buisson->rayon() + 2*(*it)->rayon())
                {
                    posOk = false;
                    break;
                }
                posOk = true;
            }
            if(posOk)
            {
                for(auto it = m_libuisson.begin();it<m_libuisson.end();it++)
                {
                    if(sqrt(pow(buisson->x() - (*it)->x(),2) + pow(buisson->y() - (*it)->y(),2)) < buisson->rayon() + (*it)->rayon())
                    {
                        posOk = false;
                        break;
                    }
                    posOk = true;
                }
            }
        }

        this->addItem(buisson);
        m_libuisson.push_back(buisson);
    }
        /*
        buisson = new Buisson(pos,this,(rand()%2+1) * 100);
        posOk = false;
        while(!posOk)
        {
            polygon.clear();
            polygon.append(buisson->mapToScene(buisson->boundingRect()));
            litem = items(polygon,Qt::IntersectsItemBoundingRect);

            int signe1 = (float)(rand()%100)/100 >= 0.5 ? 1 : -1;
            int signe2 = (float)(rand()%100)/100 >= 0.5 ? 1 : -1;
            int val = rand()%400;
            int val2 = rand()%200;

            buisson->setX(signe1 * val);
            buisson->setY(signe2 * val2);

            if(litem.count()==0) posOk=true;
        }*/


    /*for(int i=0;i<50;i++)
    {
        int signe1 = (float)(rand()%100)/100 >= 0.5 ? 1 : -1;
        int signe2 = (float)(rand()%100)/100 >= 0.5 ? 1 : -1;
        int val = rand()%800;
        int val2 = rand()%400;
        while(sqrt(pow(val,2)+pow(val2,2)) < (int)(i%3)*50)
        {
            val = rand()%800;
            val2 = rand()%400;
        }

        pos.setX(signe1 * val);
        pos.setY(signe2 * val2);
        buisson = new Buisson(pos,this,(rand()%2+1) * 1000);
        this->addItem(buisson);
    }*/
}

void Actualisation::onAccelerateButtonClicked()
{
    if(m_timer->interval() != 4)
        m_timer->setInterval(m_timer->interval()/2);
    if(m_timer->interval() == 4)
        m_window->disableAccelerateButton();
    m_window->enableDecelerateButton();
}

void Actualisation::onDecelerateButtonClicked()
{
    if(m_timer->interval() != 64)
        m_timer->setInterval(m_timer->interval()*2);
    if(m_timer->interval() == 64)
        m_window->disableDecelerateButton();
    m_window->enableAccelerateButton();
}

void Actualisation::onPauseButtonClicked()
{
    if(m_timer->isActive())
        m_timer->stop();
    else
        m_timer->start();
    m_window->changePauseButton();
}

void Actualisation::addRemovedPheromones(Pheromone* phe)
{
    m_liremovedpheromones.append(phe);
}

Buisson* Actualisation::collisionBuisson(Fourmi * const fourmi)
{
    QPolygonF polygon;
    polygon.append(fourmi->mapToScene(fourmi->boundingRect()));
    QList<QGraphicsItem *> litem = items(polygon,Qt::IntersectsItemBoundingRect);

    foreach (QGraphicsItem *item, litem) {
        if (item->type() != 103)
            continue;

        Buisson * buisson = dynamic_cast<Buisson *>(item);
        return buisson;
    }
    return NULL;
    /*
    float posXfourmi = fourmi->x();
    float posYfourmi = fourmi->y();

    for(auto it = this->m_libuissons.begin(); it != this->m_libuissons.end(); it++)
    {
        int rayon = (*it)->rayon();
        float dx = abs((*it)->x()-posXfourmi);
        float dy = abs((*it)->y()-posYfourmi);

        if(dx < rayon && dy < rayon)
        {
            return (*it);
        }
    }
    return NULL;*/
}

Pheromone* Actualisation::collisionPheromone(Fourmi* fourmi, bool haveFood)
{
    /*QList<QGraphicsItem*> items = fourmi->collidingItems();
    for(auto it = items.begin(); it != items.end(); it++)
    {
        if((*it)->type() == 100)
        {
            Pheromone* phe = (Pheromone*)(*it);
            return phe;
        }
    }
    return NULL;*/

    QPolygonF polygon;
    polygon.append(fourmi->mapToScene(fourmi->boundingRect()));
    QList<QGraphicsItem *> litem = items(polygon,Qt::IntersectsItemBoundingRect);

    foreach (QGraphicsItem *item, litem) {
        if (item->type() != 100)
            continue;

        Pheromone * phe = dynamic_cast<Pheromone *>(item);
        if(haveFood) phe->actualizeCycle();
        return phe;
    }
    return NULL;

    /*for(auto it = m_lipheronomes.begin(); it != m_lipheronomes.end(); it++)
    {
        int rayon = (*it)->rayon();

        if(abs((*it)->x() - fourmi->x())<rayon+3
                && abs((*it)->y() - fourmi->y())<rayon+3)
        {
            if(haveFood) (*it)->actualizeCycle();
            return (*it);
        }
    }
    return NULL;*/
}

void Actualisation::createPheromone(Fourmi* fourmi)
{
    Pheromone* renewphe = NULL;
    // On regarde tout d'abord si nous n'avons pas de pheromone retiré qui peuvent etre réutilisé
    foreach(Pheromone* phe, m_liremovedpheromones)
    {
        if(sqrt(pow(phe->x() - fourmi->x(),2)+pow(phe->y()-fourmi->y(),2)) < fourmi->rayon())
        {
            renewphe = phe;
            phe->actualizeCycle();
            addItem(phe);
            m_liremovedpheromones.removeOne(phe);
            return;
        }
    }
    if(NULL == renewphe)
    {
        // Puis on test la collision avec les pheromones existant pour savoir s'il faut actualiser un phéromone ou en créer un nouveau
        Pheromone* result = collisionPheromone(fourmi, true);
        if(NULL == result)
        {
            float posX = fourmi->x();
            float posY = fourmi->y();
            QVector2D pos(posX,posY);
            Pheromone* pt = new Pheromone(pos,this);
            addItem(pt);
        }
    }
}

void Actualisation::createReine(Fourmiliere* fourmiliere)
{
    QVector2D pos(fourmiliere->x(),fourmiliere->y());
    Reine* reine = new Reine(this, pos);
    addItem(reine);
}

void Actualisation::createFourmiliere(QVector2D &pos)
{
    Fourmiliere * fourmiliere = new Fourmiliere(pos, this);
    this->m_lifourmilieres.append(fourmiliere);
    this->addItem(fourmiliere);
}

bool Actualisation::onAreaToCreateFourmiliere(Fourmi* fourmi)
{
    for(auto it = this->m_lifourmilieres.begin(); it != this->m_lifourmilieres.end(); it++)
    {
        if(sqrt(pow((*it)->x() - fourmi->x(),2) + pow((*it)->y() - fourmi->y(),2)) < 300)
        {
            return false;
        }
    }
    // Test distance avec les buissons
    for(auto it = m_libuisson.begin();it<m_libuisson.end();it++)
    {
        if( sqrt(pow((*it)->x() - fourmi->x(),2) + pow((*it)->y() - fourmi->y(),2)) < 2*fourmi->rayon() + 2*(*it)->rayon())
        {
            return false;
        }
    }
    return true;
}
