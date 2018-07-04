#ifndef SNAKEGAME_BONUS_H
#define SNAKEGAME_BONUS_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "mainGame.h"

struct BonusNode   //!** Typ bazowy owocu
{
    int y, x;   //!** Wspolrzedne
    bool isToxic;   //!** Flaga dzilania Bonusu
    struct BonusNode *next;    //!** Wskaznik na kolejny element na liscie
};

struct Bonus   //!** Typ bazowy listy owocow
{
    struct BonusNode *front; //!** Wskaznik na poczatek listy
};

struct Bonus *createList();    //!** Funkcja tworzaca liste
struct Bonus*insertFront(struct Bonus *, struct BonusNode *);   //!** Funkcja wstawiajaca element na poczatku listy
bool insertNode(struct Bonus **);  //!** dodanie elementu wraz z flaga
struct BonusNode *findPrevNode(struct BonusNode *, int , int); //!** Wyszukiwanie elementu poprzedniego
void deleteAfter(struct BonusNode *);  //!** Funkcja usuwajaca element z listy za podanym elementem
bool deleteNode(struct Bonus **, int, int, bool *);    //!** Usuwa element o podanych wpsolrzednych
void printList(struct Bonus);  //!** Wyswietlanie bonusow
void removeBonus(struct Bonus **);  //!** Usuwanie bonusow
bool searchList(struct Bonus, int, int);   //!** Wyszukiwanie bonusu o podanych wspolrzednych

#endif
