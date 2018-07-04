#include "mainGame.h"

int main(int argc, char *argv[])
{
    srand(time(NULL));

    if(levels == EASY)
    {
        snake = createSnake(); /*** tworzy ciało węża ***/
        removeObstacles(&obstacle);
        removeBonus(&bonus);
    }
    else if(levels == NORMAL)
    {
        bonus = createList(); /*** tworzy bonusy w grze ***/
        snake = createSnake(); /*** tworzy ciało węża ***/
        removeObstacles(&obstacle);
    }
    else if(levels == HARD)
    {
        bonus = createList(); /*** tworzy bonusy w grze ***/
        obstacle = creatObstacle(); /*** tworzy przeszkody ***/
        snake = createSnake(); /*** tworzy ciało węża ***/
    }
    setup(&argc, argv); /*** odpowiada za wyswietlanie przy pomocy biblioteki OpenGL ***/
    return 0;
}