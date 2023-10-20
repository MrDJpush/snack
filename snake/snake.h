#ifndef __SNAKE_H__
#define __SNAKE_H__
#include <list>
#include <stdlib.h>
#include "body.h"
#include "map.h"
#include "food.h"
using namespace std;

class snake
{
public:
    friend void snake_game();
    friend void creat_food(int c,snake &s1);
    friend bool touc_self(snake &s1);
    snake(float sp=0.5,touch &tc=touch::t):t{&tc},speed(sp)
    {
        
        //创建一节身体
        int x = (rand() % 7+3) * 40;
        int y = (rand() % 6+3) * 40;
        int z;
        s.emplace_back(x,y,0xff);
        if(x>7)
        {
            z=2;
            s.emplace_back(x+40,y,0xff);
        }
        else if(y>6)
        {
            z=0;
            s.emplace_back(x,y+40,0xff);
        }
        else if(x<7)
        {
            z=3;
            s.emplace_back(x-40,y,0xff);
        }
        else 
        {
            z=1;
            s.emplace_back(x,y-40,0xff);
        }
        dir = static_cast<dirction>(z);
        cout<<"snake构造"<<endl;
    }


    void display()
    {
        auto it=s.begin();
        for(it;it!=s.end();it++)
        {
            
            it->display(it->get_color());
        }
    }

    //移动蛇
    void move_snake();

    //移动链表元素
    void list_move();
    
    void eat_food()
    {
        s.emplace_back(0,0,0xff);
        auto it=s.back();
        point p=it.get_point();
        list_move();
    }



    point if_same(int x0,int y0);
private:
    list<body> s;//身体容器
    dirction dir;
    touch *t;
    float speed;
};

#endif