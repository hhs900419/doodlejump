#include "floor.h"

#include <QDebug>
//class: floor
floor::floor()
{

}

floor::floor(int a , int b)
{
    setPixmap(QPixmap(":/images/normal_floor").scaled(150,30));
    setPos(a, b);

}

int floor :: stepped()
{
    return 0;
}


//class: disappearing_floor
disappearing_floor:: disappearing_floor(int a , int b)
{
    setPixmap(QPixmap(":/images/disappearing_floor").scaled(150,30));
    setPos(a, b);
}

int disappearing_floor:: stepped()
{
    this->scene()->removeItem(this);
    delete this;
    return 1;
}

//class: bouncy_floor
bouncy_floor::bouncy_floor(int a , int b)
{
    setPixmap(QPixmap(":/images/bouncy_floor").scaled(150,30));
    setPos(a, b);
}

int bouncy_floor :: stepped()
{
    return 2;
}

//class: moving floor
moving_floor::moving_floor(int a , int b)
{
    setPixmap(QPixmap(":/images/moving_floor").scaled(150,30));
    setPos(a, b);
    status = 1;
}

int moving_floor :: stepped()
{
    return 0;
}

void moving_floor :: moving()
{

    if(status)
        setPos(x()+1.5, y());
    else
        setPos(x()-1.5, y());
    if(x() <= 20){
        status = 1;
    }
    else if(x()+pixmap().width()>=820){
        status = 0;
    }
}
