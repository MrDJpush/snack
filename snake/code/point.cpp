#include"point.h"

bool operator==(const point &p1,const point &p2)
{
    if(p1.x==p2.x&&p1.y==p2.y)
        return true;
    else
        return false;
}