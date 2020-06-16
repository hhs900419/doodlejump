#ifndef BLACKHOLE_H
#define BLACKHOLE_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QList>

class blackhole: public QObject, public QGraphicsPixmapItem
{
public:
    blackhole();
    blackhole(int ,int);
};

#endif // BLACKHOLE_H
