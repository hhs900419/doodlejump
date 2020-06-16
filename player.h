#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QList>

class player : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    player();
    bool collide_with_monster();
    bool collide_with_blackhole();
    bool collide_with_prop();
private:
    //double v , g;
};

#endif // PLAYER_H
