#ifndef PROP_H
#define PROP_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include "prop_base.h"

class rocket: public prop_base
{
    Q_OBJECT
public:
    rocket();
    rocket(int,int);
    virtual int collided();
};

class ultimatestar: public prop_base
{
    Q_OBJECT
public:
    ultimatestar();
    ultimatestar(int a , int b);
    virtual int collided();

};



#endif // PROP_H
