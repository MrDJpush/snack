#ifndef __map_H__
#define __map_H__
#include"point.h"
#include<string.h>
class map
{
private:
    int mp[15][12];
    int bcolor;
    lcd *l;
public:
    map(int c,lcd &l=lcd::l);
    void display_map()
    {
        int i,j;
        for(i=0;i<12*40;i++)
        {
            for(j=0;j<15*40;j++)
            {
                l->display_point(j,i,bcolor);
            }
        }
        
    }
};


#endif