#include "player.h"
#include "monster.h"
#include "blackhole.h"
#include "prop.h"

player::player()
{
    setPixmap(QPixmap(":/images/doodle").scaled(120,120));
}

bool player::collide_with_monster()
{
    QList<QGraphicsItem *> collision = collidingItems();
    foreach(QGraphicsItem *obj , collision){
        monster *m = dynamic_cast<monster*>(obj);
        if(m){
            return true;
        }
    }
    return false;
}

bool player::collide_with_blackhole()
{
    QList<QGraphicsItem *> collision = collidingItems();
    foreach(QGraphicsItem *obj , collision){
        blackhole *bh = dynamic_cast<blackhole*>(obj);
        if(bh){
            return true;
        }
    }
    return false;
}
bool player::collide_with_prop()
{
    QList<QGraphicsItem *> collision = collidingItems();
    foreach(QGraphicsItem *obj , collision){
        prop_base *prop = dynamic_cast<prop_base*>(obj);
        if(prop){
            return true;
        }
    }
    return false;
}
