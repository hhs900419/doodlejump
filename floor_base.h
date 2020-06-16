#ifndef FLOOR_BASE_H
#define FLOOR_BASE_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

class floor_base : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    floor_base();
    virtual int stepped()=0;


private:

};



#endif // FLOOR_BASE_H
