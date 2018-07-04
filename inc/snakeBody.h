#include <stdbool.h>
#include <stdlib.h>

#ifndef SNAKEGAME_SNAKEBODY_H
#define SNAKEGAME_SNAKEBODY_H

struct SnakeQueueNode   //!** typ bazowy elementu weza
{
    int y, x;   //!** wspolrzedne
    struct SnakeQueueNode *prev, *next; //!** wskaznik na poprzedni element weza i nastepny
};

struct SnakeQueue   //!** typ bazowy calego weza - kolejka
{
    struct SnakeQueueNode *head, *tail;
    int size;
};

bool pushFront(struct SnakeQueue *, int, int);  //!** dodaje element o podanych wspolrzednych na poczatek kolejki
bool pushBack(struct SnakeQueue *, int, int);   //!** dodaje element o podanych wspolrzednych na koniec kolejki
bool popBack(struct SnakeQueue *);  //!** usuwa element z konca kolejki
bool searchQueue(struct SnakeQueue, int, int);  ///!** wyszukiwanie elementu o podanych wspolrzednych
int getSize(struct SnakeQueue *);   //!** pobieranie rozmiaru weza
bool isEmpty(struct SnakeQueue);    //!** istnienie weza

#endif
