#include <GL/gl.h>
#include <GL/glut.h>
#include "snakeInterface.h"
#include "Point.h"

struct Snake createSnake()
{
    struct SnakeQueue *snakeQueue = (struct SnakeQueue *) malloc(sizeof(struct SnakeQueue));
    pushFront(snakeQueue, 20, 20);
    pushFront(snakeQueue, 21, 20);
    pushFront(snakeQueue, 22, 20);
    switchPoint(20, 20);
    switchPoint(20, 21);
    switchPoint(20, 22);
    struct Snake snake = {*snakeQueue};
    return snake;
}

bool moveUp(struct Snake *snake)
{
    int newY = snake->snakeQueue.head->y + 1, newX = snake->snakeQueue.head->x;
    if (!collisions(snake, newX, newY) || newY >= 39)
        return false;
    popBack(&snake->snakeQueue);
    pushBack(&snake->snakeQueue, newX, newY);
    return true;
}

bool moveDown(struct Snake *snake)
{
    int newY = snake->snakeQueue.head->y - 1, newX = snake->snakeQueue.head->x;
    if (!collisions(snake, newX, newY) || newY < 1)
        return false;
    popBack(&snake->snakeQueue);
    pushBack(&snake->snakeQueue, newX, newY);
    return true;
}

bool moveLeft(struct Snake *snake)
{
    int newY = snake->snakeQueue.head->y, newX = snake->snakeQueue.head->x - 1;
    if (!collisions(snake, newX, newY) || newX <= 0)
        return false;
    popBack(&snake->snakeQueue);
    pushBack(&snake->snakeQueue, newX, newY);
    return true;
}

bool moveRight(struct Snake *snake)
{
    int newY = snake->snakeQueue.head->y, newX = snake->snakeQueue.head->x + 1;
    if (!collisions(snake, newX, newY) || newX >= 39)
        return false;
    popBack(&snake->snakeQueue);
    pushBack(&snake->snakeQueue, newX, newY);
    return true;
}

enum Status moveSnake(struct Snake *snake)
{
    switch (dir)
    {
        case UP:
            if (!moveUp(snake))
                return FAIL;
            break;
        case DOWN:
            if (!moveDown(snake))
                return FAIL;
            break;
        case RIGHT:
            if (!moveRight(snake))
                return FAIL;
            break;
        case LEFT:
            if (!moveLeft(snake))
                return FAIL;
            break;
        default:
            break;
    }
    return SUCCESS;
}

void eatBonus(struct Snake *snake, int x, int y)
{
    bool isToxic;
    deleteNode(&bonus, x, y, &isToxic);
    if (isToxic)
        popBack(&snake->snakeQueue);
    else
        pushFront(&snake->snakeQueue, x + 1, y + 1);
    insertNode(&bonus);
}

void display(struct Snake snake)
{
    struct SnakeQueueNode *head = snake.snakeQueue.head;
    glColor3d(1, 1, 0.25);
    glRectd(head->x, head->y, head->x + 1, head->y + 1);
    head = head->next;
    while(head)
    {
        glRectd(head->x, head->y, head->x + 1, head->y + 1);
        head = head->next;
    }
}