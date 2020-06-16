#include "prop.h"
#include "player.h"

rocket::rocket()
{

}
rocket::rocket(int a , int b)
{
    setPixmap(QPixmap(":/images/rocket").scaled(120,120));
    setPos(a, b);
}
int rocket::collided()
{
    return 1;
}
ultimatestar::ultimatestar()
{

}
ultimatestar::ultimatestar(int a , int b)
{
    setPixmap(QPixmap(":/images/star").scaled(120,120));
    setPos(a, b);
}
int ultimatestar::collided()
{
   return 2;
}
