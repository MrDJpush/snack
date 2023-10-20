#include "body.h"

void body::move(dirction d)
{
    switch (d)
    {
    case UP:
        begin_point.y -= height;
        break;

    case DOWN:
        begin_point.y += height;
        break;

    case LEFT:
        begin_point.x -= width;
        break;
    case RIGHT:
        begin_point.y += height;
        break;
    
    default:
        break;
    }
}




