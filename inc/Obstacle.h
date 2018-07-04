#ifndef SNAKEGAME_OBSTACLE_H
#define SNAKEGAME_OBSTACLE_H

#include <stdbool.h>

int x, y; //!** zmienne pomocnicze

struct ObstacleNode //!** typ bazowy przeszkody
{
    int x, y;  //!** wspolrzedna
    struct ObstacleNode *next;   //!** wskaznik na kolejny element listy
};

struct Obstacle //!** typ bazowy listy przeszkod
{
    struct ObstacleNode *front; //!** wskaznik na pcozatek listy
};

struct Obstacle *creatObstacle();   //!** funkcja tworzaca liste z przeszkodami dla weza
struct Obstacle *insertObstacleFront(struct Obstacle *, struct ObstacleNode *); //!** funkcja wstawiajaca element na poczatku listy przeszkod
bool insertObstacle(struct Obstacle **, int, int);   //!** funkcja wstawiajaca przeszkode do listy
void printObstacle(struct Obstacle);    //!** funkcja drukujaca liste przeszkod
void removeObstacles(struct Obstacle **);  //!** Usuwanie przeszkod
bool searchObstacle(struct Obstacle, int, int); //!** funkcja przeszukujaca liste w celu znalezienia przeszkodzo o podanym x i y

#endif
