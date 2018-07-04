#include <GL/gl.h>
#include <GL/glut.h>
#include "Frame.h"

void drawFrame(int frameWidth, int frameHeight)
{
    for(int i = 0; i < frameWidth; i++)
        for(int j = 0; j < frameHeight; j++)
            unit(i, j, 1.0, 1.0, 1.0);

}

void unit(int x, int y, float r, float g, float b)
{
    if(0 == x || 0 == y || x == 40 - 1 || y == 40 - 1)
    {
        glColor3f(r, g, b);
        glVertex2f(x, y);
        glVertex2f(x + 1, y);
        glVertex2f(x + 1, y + 1);
        glVertex2f(x, y + 1);
        glRectd(x, y, x + 1, y + 1);
    }
}
