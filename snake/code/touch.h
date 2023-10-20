#ifndef __TOUCH_H__
#define __TOUCH_H__
#include "point.h"

enum dirction
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

struct touch_info
{
    int x=0;//终点坐标
    int y=0;//终点坐标
    enum dirction dir=UP;//滑动方向
};

class touch
{
public:
    
    ~touch();

    //获取触摸事件信息：触摸点的坐标和滑动方向
    touch_info get_touch_info();

    touch(const touch & other) = delete;
private:
    touch(const char * pathname = "/dev/input/event0");
    int fd;

public:
    static touch t;
};


#endif