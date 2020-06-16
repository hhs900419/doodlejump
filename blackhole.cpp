#include "blackhole.h"

blackhole::blackhole()
{
    setPixmap(QPixmap(":/images/black_hole").scaled(150,150));
}
blackhole::blackhole(int a,int b)
{
    setPixmap(QPixmap(":/images/black_hole").scaled(150,150));
    setPos(a, b);
}
