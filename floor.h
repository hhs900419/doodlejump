#ifndef FLOOR_H
#define FLOOR_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include "floor_base.h"

class floor : public floor_base
{
    Q_OBJECT
public:
    floor();
    floor(int a , int b);
    //virtual void stepped(floor_base *f);
    virtual int stepped();

private:

};

class disappearing_floor : public floor_base
{
    Q_OBJECT
public:
    disappearing_floor();
    disappearing_floor(int a , int b);
    //virtual void stepped(floor_base *f);
    virtual int stepped();
private:
};

class bouncy_floor : public floor_base
{
    Q_OBJECT
public:
    bouncy_floor();
    bouncy_floor(int a , int b);
    virtual int stepped();

private:

};
class moving_floor : public floor_base
{
    Q_OBJECT
public:
    moving_floor();
    moving_floor(int a , int b);
    virtual int stepped();

public slots:
    void moving();

private:
    bool status;
};
#endif // FLOOR_H
