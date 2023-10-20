#include <iostream>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <stdlib.h>
#include "touch.h"
using std::cerr;
touch touch::t{"/dev/input/event0"};

touch::touch(const char * pathname)
{
    fd = open(pathname,O_RDONLY);
    if(fd == -1)
    {
        cerr << "open event0 error";
    }
}

touch::~touch()
{
    close(fd);
}


touch_info touch::get_touch_info()
{
    touch_info info;
    int x=-1,y=-1;//保存起点坐标
    int r;
    struct input_event ev;
    while(1)//不能只读取1次或者2次，因为即使手指触摸一下，也会产生多个 struct input_event 数据
            //你没有办法保证你得到的就是你想要的
            //正确的做法是循环读取，直到达到你的目的为止
    {
        r = read(fd,&ev,sizeof(ev));
        if(r == -1)//读取失败，结束循环
        {
            perror("read fail");
            break;
        }
        if(r == 0)//没有读到数据，重新读取。不需要往下走
            continue;

        if(ev.type==EV_ABS && ev.code==REL_X&&ev.value<1024&&ev.value>0)
        {
            if(x == -1)
                x = ev.value*0.78125;
            info.x = ev.value*0.78125;
        }

        if(ev.type==EV_ABS && ev.code==REL_Y&&ev.value<600&&ev.value>0)
        {
            if(y == -1)
                y = ev.value*0.8;
            info.y = ev.value*0.8;
        }

        if(ev.type == EV_KEY && ev.code == BTN_TOUCH && ev.value == 0)//手指松开
        {
            break;
        }
        //下面的代码就是对数据进行处理
        //printf("type=%d,code=%d,value=%d\n",ev.type,ev.code,ev.value);
    }

    //根据起点和终点坐标得到滑动方向
    //思路：分4种情况
    //向上：起点y坐标大于终点y坐标并且 △y大于△x
    //向下：起点y坐标小于终点y坐标并且 △y大于△x
    //向左：起点x坐标大于终点x坐标并且 △x大于△y
    //向左：起点x坐标小于终点x坐标并且 △x大于△y
    if(y > info.y && (y-info.y)*(y-info.y) > (x-info.x)*(x-info.x))
    {
        info.dir = UP;
    }
    else if(y < info.y && (y-info.y)*(y-info.y) > (x-info.x)*(x-info.x))
    {
        info.dir = DOWN;
    }
    else if(x > info.x && (y-info.y)*(y-info.y) < (x-info.x)*(x-info.x))
    {
        info.dir = LEFT;
    }
    else
    {
        info.dir = RIGHT;
    }

    return info;
}