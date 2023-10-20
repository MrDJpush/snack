#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include "lcd.h"
#include "touch.h"
#include "snake.h"
#include "food.h"
#include"map.h"
int main()
{
    map p1{0xffffff};
    p1.display_map();
    srand(time(0));
    //创建一个食物
    int x = (rand() % 15) * 40;
    int y = (rand() % 12) * 40;
    food * pf = new food{x,y,0xff0000};
    pf->display();

    snake s{};

    bool b;
    while(!s.gameover())
    {
        s.clear(0xffffff);
        b = s.move(pf);
        s.display();
        if(b)
        {
            delete pf;
            int x = (rand() % 15) * 40;
            int y = (rand() % 12) * 40;
            pf = new food{x,y,0xff};
            pf->display();
        }
        sleep(1);
    }


    return 0;
}
