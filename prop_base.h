#ifndef PROP_BASE_H
#define PROP_BASE_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

class prop_base: public QObject, public QGraphicsPixmapItem
{
     Q_OBJECT
public:
    prop_base();
    virtual int collided()=0;

};

#endif // PROP_BASE_H
