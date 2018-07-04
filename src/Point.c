#include <stdlib.h>
#include "Point.h"
#include "mainGame.h"

struct Point *randomPoint()
{
    struct Point *newPoint = (struct Point *) malloc(sizeof(struct Point));
    if(newPoint)
    {
        do {
            newPoint->x = rand() % 38 + 1;
            newPoint->y = rand() % 38 + 1;
        } while (points[newPoint->x][newPoint->y]);
    }
    switchPoint(newPoint->x, newPoint->y);
    return newPoint;
}

void switchPoint(int x, int y)
{
    points[x][y] = points[x][y] ? false : true ;
}