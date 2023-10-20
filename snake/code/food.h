#ifndef __FOOD_H__
#define __FOOD_H__
#include "point.h"
#include "lcd.h"
class food:public base_point
{
public:
    food(int x,int y,int c,int t=5);

    food(const food &p);

    //扩展： 食物只能存在5秒，5秒之后没有被吃也会消失
    void disapper_food(int bcolor);

    void be_eat(int bcolor)
    {
        clear(bcolor);
    }


private:
    int time;
};


#endif
