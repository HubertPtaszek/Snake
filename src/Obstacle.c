#include <GL/gl.h>
#include <GL/glut.h>
#include "Obstacle.h"
#include "Point.h"

struct Obstacle *creatObstacle()
{
    struct ObstacleNode * newNode = (struct ObstacleNode *) malloc(sizeof(struct ObstacleNode));
    struct Obstacle * list = (struct Obstacle *) malloc(sizeof(struct Obstacle));
    struct Point * point;
    if(newNode)
    {
        point = randomPoint();
        newNode->x = point->x;
        newNode->y = point->y;
        newNode->next = NULL;
        list->front = newNode;
    }
    for(int i = 0; i <= 5; i++)
    {
        point = randomPoint();
        x = point->x;
        y = point->y;
        insertObstacle(&list, x, y);
        insertObstacle(&list, (x + 1), y);
    }
    for(int i = 6; i <= 10; i++)
    {
        point = randomPoint();
        x = point->x;
        y = point->y;
        insertObstacle(&list, x, y);
        insertObstacle(&list, x, (y + 1));
        insertObstacle(&list, x, (y + 2));
    }
    return list;
}

struct Obstacle *insertObstacleFront(struct Obstacle *list, struct ObstacleNode *newNode)
{
    newNode->next = list->front;
    list->front = newNode;
    return list;
}

bool insertObstacle(struct Obstacle **list, int x, int y)
{
    if(list == NULL)
        return false;
    struct ObstacleNode *newNode = (struct ObstacleNode *) malloc(sizeof(struct ObstacleNode));
    if(newNode)
    {
        newNode->x = x;
        newNode->y = y;
        newNode->next = NULL;
        *list = insertObstacleFront(*list, newNode);
    }
    return true;
}

void printObstacle(struct Obstacle list)
{
    for( ; list.front; list.front = list.front->next)
    {
        glColor3f(1.0, 1.0, 1.0);
        glRectd(list.front->x, list.front->y, list.front->x + 1, list.front->y + 1);
    }
}

void removeObstacles(struct Obstacle **list)
{
    struct ObstacleNode *next = NULL;
    while ((*list)->front)
    {
        next = (*list)->front->next;
        free((*list)->front);
        (*list)->front = next;
    }
}

bool searchObstacle(struct Obstacle list, int x, int y)
{
    for( ; list.front; list.front = list.front->next)
        if(list.front->x == x && list.front->y == y)
            return true;
    return false;
}


