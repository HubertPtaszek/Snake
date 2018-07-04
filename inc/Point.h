#ifndef SNAKEGAME_POINT_H
#define SNAKEGAME_POINT_H

#include <stdbool.h>

struct Point    //!** typ bazowy pukntów w ukladzie kartezjanskim
{
    int x, y;  //!** wspolrzedna
};

bool points[40][40];

struct Point *randomPoint(); //!** losowanie punktu w układzie kartezjanskim

void switchPoint(int, int); //!** ustawienie flagi na punkcie o podanych wspolrzednych

#endif