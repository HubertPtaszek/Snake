#include <GL/gl.h>
#include <GL/glut.h>
#include "Bonus.h"
#include "Point.h"

struct Bonus *createList()
{
    struct BonusNode *newNode = (struct BonusNode *) malloc(sizeof(struct BonusNode));
    struct Bonus *list = (struct Bonus *) malloc(sizeof(struct Bonus));
    struct Point *point;
    if(newNode)
    {
        point = randomPoint();
        newNode->y = point->y;
        newNode->x = point->x;
        newNode->isToxic = (rand() % 101) > 90 ? true : false;
        newNode->next = NULL;
        list->front = newNode;
    }
    for(int i = 0; i < 2; i++)
        insertNode(&list);
    return list;
}

struct Bonus *insertFront(struct Bonus *list, struct BonusNode *newNode)
{
    newNode->next = list->front;
    list->front = newNode;
    return list;
}

bool insertNode(struct Bonus **list)
{
    if(NULL == list)
        return false;
    struct BonusNode *newNode = (struct BonusNode *) malloc(sizeof(struct BonusNode));
    struct Point *point;
    if(newNode)
    {
        point = randomPoint();
        newNode->y = point->y;
        newNode->x = point->x;
        newNode->isToxic = (rand() % 11) > 9 ? true : false;
        newNode->next = NULL;
        *list = insertFront(*list, newNode);
    }
    return true;
}

struct BonusNode *findPrevNode(struct BonusNode *front, int x, int y)
{
    struct BonusNode *prev = NULL;
    while(front && (front->y != y) && (front->x != x))
    {
        prev = front;
        front = front->next;
    }
    return prev;
}

void deleteAfter(struct BonusNode *node)
{
    struct BonusNode *next = NULL != node ? node->next : NULL;
    if(next)
    {
        node->next = next->next;
        free(next);
    }
}

bool deleteNode(struct Bonus **list, int x, int y, bool *isToxic)
{
    if (NULL == list)
        return false;
    if (((*list)->front->y == y) && ((*list)->front->x == x))
    {
        *isToxic = (*list)->front->isToxic;
        struct BonusNode *next = (*list)->front->next;
        free((*list)->front);
        (*list)->front = next;
    }else
    {
        struct BonusNode *prev = findPrevNode((*list)->front, x, y);
        *isToxic = NULL == prev->next ? prev->isToxic : prev->next->isToxic;
        deleteAfter(prev);

    }
    return true;
}

void printList(struct Bonus list)
{
    for(; list.front; list.front = list.front->next)
    {
        if( true == list.front->isToxic )
            glColor3d(1.0, 0.0, 0.0);
        else
            glColor3d(0.0, 1.0, 0.0);
        glRectd(list.front->x, list.front->y, list.front->x + 1, list.front->y + 1);
    }
}

void removeBonus(struct Bonus **list)
{
    struct BonusNode *next = NULL;
    while ((*list)->front)
    {
        next = (*list)->front->next;
        free((*list)->front);
        (*list)->front = next;
    }
}

bool searchList(struct Bonus list, int x, int y)
{
    for(; list.front; list.front = list.front->next)
        if(list.front->y == y && list.front->x == x)
            return true;
    return false;
}