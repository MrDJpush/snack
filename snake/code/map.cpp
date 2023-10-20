#include"map.h"

map::map(int c,lcd &l):l(&l)
{  
    memset(mp,0,180);
    bcolor=c;
}