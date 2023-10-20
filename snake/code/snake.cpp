#include "snake.h"

void get_info(touch_info &info)
{
    while (1)
    {
        info=touch::t.get_touch_info();
        cout<<"info.x="<<info.x<<",info.y="<<info.y<<"info.dir"<<info.dir<<endl;
    }
}
