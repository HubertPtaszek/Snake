#ifndef SNAKEGAME_MAINGAME_H
#define SNAKEGAME_MAINGAME_H

#include <time.h>
#include <stdlib.h>
#include "Bonus.h"
#include "Obstacle.h"
#include "snakeInterface.h"

enum Direction {UP = 1, DOWN, RIGHT, LEFT} dir;    //!** typ wyliczeniowy - kierunek poruszania weza
enum Status {FAIL, SUCCESS} status; //!** typ wyliczeniowy do bledow
enum Level {EASY = 2, NORMAL = 1, HARD = 0} levels; //!* typ wyliczeniowy do poziomow gry
struct Bonus *bonus;    //!** bonusy w grze
struct Snake snake; //!** reprezentacja stanu weza
struct Obstacle *obstacle; //!** przeszkody w grze

void setup(int *, char **); //!** inicjajca biblioteki graficznej
void displayWindow();   //!** inicjacja okna gry
void reshapeWindow(int, int);   //!** obsluga okna gry
void timer(int);    //!** timer biblioteki graficznej
void getUserInput(int);   //!** obsluga klawiatury
bool collisions(struct Snake *, int, int);  //!** funkcja obslugujaca kolizje weza z przedmiotoami otoczenia
void end();    //!** funkcja konczaca gre

#endif
