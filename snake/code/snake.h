#ifndef __SNAKE_H__
#define __SNAKE_H__
#include <list>
#include <stdlib.h>
#include "body.h"
#include "point.h"
#include "food.h"
#include <mutex>
using namespace std;

void get_info(touch_info &info);

class snake
{
public:
    snake(float sp=0.5,touch &tc=touch::t):t{&tc},speed(sp)
    {
        //创建一节身体
        int x = (rand() % 7+3) * 40;
        int y = (rand() % 6+3) * 40;
        s.emplace_back(x,y,0xff0000);
        s.emplace_back(x,y-40,0xff0000);
        dir = static_cast<dirction>(rand() % 4);
    }

    touch_info info;

    void display()
    {
        //遍历容器，一个一个显示蛇的身体
        //..........
        for(auto it = s.begin();it!=s.end();++it)
        {
            it->display();
        }
    }

    void clear(int color)
    {
        //遍历容器，一个一个清除(变为背景色)蛇的身体
        //..........
        for(auto it = s.begin();it!=s.end();++it)
        {
            it->clear(color);
        }
    }

    //吃到食物返回   true ，否则返回 false
    bool move( food * pf)
    {
        //在第一个节点的下面插入一个新节点
        //if(没吃到食物)  删除最后一个节点
        body newfront = s.front();
        thread tid(&get_info,ref(info));        
        tid.detach();
        dir=info.dir;
        cout<<"dir"<<dir<<"info.dir"<<info.dir<<endl;
        newfront.move(dir);
        s.push_front(newfront);
        if(!((newfront.get_point())==pf->get_point()))
        {
            s.pop_back();
            return false;
        }
        else
        {
            return true;
        }
    }

    bool touc_self()const
    {
        auto it=s.begin();
        auto t=s.back();
        point p=it->get_point();
        point p1=t.get_point();
        cout<<"x="<<p1.x<<" y="<<p1.y<<endl;
        if(p.x==p1.x&&p.y==p1.y)
        return true;
        return false;
    }

    bool gameover() const
    {
        int c1=s.begin()->get_point().x;
        int c2=s.begin()->get_point().y;
        cout<<"x,y"<<c1<<","<<c2<<endl;
        if(c1>=15*40||c2>=12*40||touc_self()||c1<=0||c2<=0)
        {
            return true;
        }
        return false;
    }

private:
    list<body> s;//身体容器
    dirction dir;
    touch *t;
    float speed;
};

#endif