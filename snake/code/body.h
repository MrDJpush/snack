#ifndef __BODY_H__
#define __BODY_H__

#include "point.h"
#include "lcd.h"
class body:public base_point
{
public:
body(int x,int y,int c):base_point(x,y,c)
{}

body(const body &p):base_point(p)
{
}

void move(dirction d);

};


#endif
