#include <GL/gl.h>
#include <GL/glut.h>
#include <AL/al.h>
#include <AL/alc.h>
#include "mainGame.h"
#include "Frame.h"
#include "snakeInterface.h"
#include "Point.h"
#include "Obstacle.h"

#define WIDTH 40
#define HEIGHT 40

void setup(int *argc, char **argv)
{
    dir = LEFT;
    status = SUCCESS;
    levels = HARD;
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(500, 500);
    glutCreateWindow("SNAKE MINI GAME");
    glutDisplayFunc(displayWindow);
    glutReshapeFunc(reshapeWindow);
    glutTimerFunc(0, timer, 0);
    glutSpecialFunc(getUserInput);
    glutMainLoop();
}

void displayWindow() {
    if (status == FAIL || isEmpty(snake.snakeQueue)) {
        glClear(GL_COLOR_BUFFER_BIT);
        end();
    } else
    {
        if (levels == EASY)
        {
            glClear(GL_COLOR_BUFFER_BIT);
            drawFrame(WIDTH, HEIGHT);
            status = moveSnake(&snake);
            display(snake);
        }else if (levels == NORMAL)
        {
            glClear(GL_COLOR_BUFFER_BIT);
            drawFrame(WIDTH, HEIGHT);
            status = moveSnake(&snake);
            printList(*bonus);
            display(snake);
        } else if (levels == HARD)
        {
            glClear(GL_COLOR_BUFFER_BIT);
            drawFrame(WIDTH, HEIGHT);
            status = moveSnake(&snake);
            printObstacle(*obstacle);
            printList(*bonus);
            display(snake);
        }
    }
    glutSwapBuffers();
}

void reshapeWindow(int width, int height)
{
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, WIDTH, 0.0, HEIGHT, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

void timer(int _)
{
    glutPostRedisplay();
    glutTimerFunc(1000/10, timer, 0);
}

void getUserInput(int key)
{
    switch (key)
    {
        case GLUT_KEY_LEFT:
            if (dir != RIGHT || dir != LEFT) dir =  LEFT;
            break;
        case GLUT_KEY_RIGHT:
            if (dir != LEFT || dir != RIGHT) dir = RIGHT;
            break;
        case GLUT_KEY_DOWN:
            if (dir != UP || dir != DOWN) dir = DOWN;
            break;
        case GLUT_KEY_UP:
            if (dir != DOWN || dir != UP) dir = UP;
            break;
        case GLUT_KEY_F1:
            if (levels != EASY ) levels = EASY;
            break;
        case GLUT_KEY_F2:
            if (levels = NORMAL) levels = NORMAL;
            break;
        case GLUT_KEY_F3:
            if (levels = HARD) levels = HARD;
            break;
        default:
            break;
    }
}

bool collisions(struct Snake *snake, int x, int y)
{
    if(points[x][y])
    {
        if(searchList(*bonus, x, y))
        {
            eatBonus(snake, x, y);
            return true;
        }
        if(searchQueue(snake->snakeQueue, x, y) || searchObstacle(*obstacle, x, y))
            return false;
    }
    return true;
}

void end()
{
    char end[64] = "GAME OVER";
    char score[10];
    drawFrame(WIDTH, HEIGHT);
    sprintf(score, "SCORE: %d", getSize(&snake.snakeQueue) - 3);
    glColor3f(1, 1, 1);
    glPushMatrix();
    glTranslatef(0.8, 22, 0);
    glScalef(0.04, 0.04, 0.04);
    for (int i = 0; end[i] != 0; ++i)
        glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, end[i]);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(13, 15, 0);
    glScalef(0.02, 0.02, 0.02);
    for (int i = 0; score[i] != 0; ++i)
        glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, score[i]);
    glPopMatrix();
}