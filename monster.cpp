#include "monster.h"
#include "player.h"
#include "bullet.h"


monster::monster()
{

}
monster::monster(int a , int b)
{
    if (rand()%2 == 1){
        setPixmap(QPixmap(":/images/monster1").scaled(120,120));
    }
    else {
        setPixmap(QPixmap(":/images/monster 2").scaled(120,120));
    }
    setPos(a, b);

}

bool monster::collide_with_bullet()
{
    QList<QGraphicsItem *> collision = collidingItems();
    foreach(QGraphicsItem *obj , collision){
        bullet *b = dynamic_cast<bullet*>(obj);
        if(b){
            return true;
        }
    }
    return false;
}

/*bool monster::collide_with_doodle()
{
    QList<QGraphicsItem *> collision = collidingItems();
    foreach(QGraphicsItem *obj , collision){
        player *p = dynamic_cast<player*>(obj);
        if(p){
            return true;
        }
    }
    return false;
}*/
