#ifndef __POINT_H__
#define __POINT_H__
#include <iostream>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <stdlib.h>
#include"lcd.h"
#include"touch.h"
#include<thread>

struct point
{
    friend bool operator==(const point &p1,const point &p2);
    bool operator==(const point &p)
     {
        if(x==p.x&&y==p.y)
        return true;
        else
        return false;
     }
    int x;
    int y;
    point(int x=0,int y=0)
    {
        this->x = x;
        this->y = y;
    }
    point(const point &p)
    {
        this->x = p.x;
        this->y = p.y;
    }
};

class base_point
{
public:

    base_point(int x,int y,int c,lcd &l=lcd::l):height(40),width(40),begin_point(x,y),color(c),l(&l){}

    base_point(const base_point &p,int c):height(40),width(40),begin_point(p.begin_point),l(p.l),color(c){}

    void display() const
    {
        int i,j;
        for(i=begin_point.y;i<height+begin_point.y;i++)
        {
            for(j=begin_point.x;j<width+begin_point.x;j++)
            {
                l->display_point(j,i,color);
            }
        }
    }
    void clear(int c) const
    {
        int i,j; 
        for(i=begin_point.y;i<height+begin_point.y;i++)
        {
            for(j=begin_point.x;j<width+begin_point.x;j++)
            {
                l->display_point(j,i,c);
            }
        }
    }
    void movec(int r)
    {
        if(r==0)
            begin_point.y-=40;
        else if(r==1)
            begin_point.y+=40;
        else if(r==1)
            begin_point.x-=40;
        else if(r==1)
            begin_point.x+=40;
    }

    point get_point()const
    {
        return begin_point;
    }

    void  change_point(point &p)
    {
        begin_point=p;
    }

    int get_color()
    {
        return color;
    }

protected:
    point begin_point;//食物起点坐标
    const int height;
    const int width;
    int color;//身体颜色
    lcd * l;
};

#endif