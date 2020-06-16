#include "bullet.h"
#include "monster.h"
#include <QDebug>
bullet::bullet()
{

}

void bullet::fly()
{

    setPos(x(), y() - 7);
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for(int i=0 , n=colliding_items.size(); i<n; ++i){
        if(typeid (*(colliding_items[i])) == typeid (monster)){
            this->setPos(-100 , this->y());
            colliding_items[i]->setPos(-500 , colliding_items[i]->y());
            scene()->removeItem(colliding_items[i]);


        }
    }
    if(y() < 0) {
        this->scene()->removeItem(this);
        delete this;
    }

}

void bullet::bullet_bye_bye()
{
    this->scene()->removeItem(this);
    delete this;
}
