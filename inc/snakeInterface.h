#ifndef SNAKEGAME_SNAKEINTERFACE_H
#define SNAKEGAME_SNAKEINTERFACE_H

#include "mainGame.h"
#include "snakeBody.h"
#include "Bonus.h"

struct Snake    //!** Typ bazowy przechowujacy budowe weza
{
    struct SnakeQueue snakeQueue;   //!** Kolejka z cialem weza
};

struct Snake createSnake(); //!** Funkcja tworzy nowego weza
bool moveUp(struct Snake *);    //!** Funkcja ruchu w gore
bool moveDown(struct Snake *);  //!** Funkcja ruchu w dol
bool moveRight(struct Snake *); //!** Funkcja ruchu w prawo
bool moveLeft(struct Snake *);  //!** Funkcja ruchu w lewo
enum Status moveSnake(struct Snake *);  //!** Obsluga ruchu weza
void eatBonus(struct Snake *, int, int);    //!** usuwanie zjedzonego bonusu i zmiana wielkosci weza
void display(struct Snake);

#endif
