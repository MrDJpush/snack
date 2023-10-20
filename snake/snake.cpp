#include"snake.h"

struct touch_info info;

void get_info(touch *t)
{
    while (1)
    {
        info=t->get_touch_info();
    }
}

void snake::move_snake()
{
    int r,x0,y0;
    r=0;
    auto it=s.begin();
    thread tid{get_info,t}; 
    tid.detach();
    do
    {   
        r=dir;
        x0 = info.x;
        y0 = info.y;
        //根据滑动方向去改变二维数组中的数字
        sleep(speed);
        list_move();
        it->move(r);
        dir = info.dir;
    }while (r==dir);
}

void snake::list_move()
{
    auto t=s.begin();
    for(t;t!=s.end();)
    {
        auto it=t;
        ++t;
        t->change_point(it->get_point());
    }
}

point snake::if_same(int x0,int y0)
{
    auto it=s.begin();
    for(it;it!=s.end();it++)
    {
        point p=it->get_point();
        if(x0==p.x&&y0==p.y)
        {
            if(x0>7&&y0>6)
            {
                --x0;
                --y0;
            }
            else if(y0>6&&x0<7)
            {
                --y0;
                ++x0;
            }
            else if(y0<6&&x0<7)
            {
                ++y0;
                ++x0;
            }else
            {
                --x0;
                ++y0;
            }
            if_same(x0,y0);
        }
    }
    return point(x0,y0);
}

void creat_food(int c,snake &s1)
{
    while(1)
    {
        int x = (rand() % 15) * 40;
        int y = (rand() % 12) * 40;
        auto it=s1.s.begin();
        point p1=s1.if_same(x,y);
        food f{p1.x,p1.y,0xff00ff};
        f.display(0x00ff00);
        for(it;it!=s1.s.end();it++)
        {
            point p=it->get_point();
            if(p1.x==p.x&&p1.y==p.y)
            {
                s1.eat_food();
                f.be_eat(0xffffff);
            }
        }
    }
}

bool touc_self(snake &s1)
{
    auto it=s1.s.begin();
    auto t=s1.s.back();
    point p=it->get_point();
    point p1=t.get_point();
    cout<<"x="<<p1.x<<" y="<<p1.y<<endl;
    if(p.x==p1.x&&p.y==p1.y)
    return true;
    return false;
}

void snake_game()
{
    snake s;
    int x0,y0;
    map p(0xffffff);
    p.display_map();
    thread t1{&creat_food,0xffffff,ref(s)};
    t1.detach();
    while (1)
    {
        s.display();
        s.move_snake();
        s.display();
        int c1=s.s.begin()->get_point().x;
        int c2=s.s.begin()->get_point().y;
        cout<<"x,y"<<c1<<","<<c2<<endl;
        cout<<"size"<<s.s.size()<<endl;
        if(c1>=15*40||c2>=12*40||touc_self(s))
        {
            return ;
        }
    }
}
