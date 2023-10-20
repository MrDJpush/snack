#include "food.h"

food::food(int x,int y,int c,int t):base_point(x,y,c),time(t)
{
}

food::food(const food &p):base_point(p),time(p.time)
{
}



void food::disapper_food(int bcolor)
{
    sleep(time);
    clear(bcolor);
    delete this;
}