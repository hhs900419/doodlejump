#ifndef MONSTER_H
#define MONSTER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QList>

class monster: public QObject, public QGraphicsPixmapItem
{
public:
    monster();
    monster(int a,int b);
    bool collide_with_bullet();
};

#endif // MONSTER_H
