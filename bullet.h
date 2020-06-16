#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QList>
#include "monster.h"

class bullet : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    bullet();
    bool bullet_gameover=false;

public slots:
    void fly();
    void bullet_bye_bye();
};

#endif // BULLET_H
