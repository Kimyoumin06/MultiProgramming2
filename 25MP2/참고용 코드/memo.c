#include <iostream>
#include <math.h>
#include <stdio.h>
#include <Windows.h>

#define PI 3.14159226535897

int drawPoint(int x, int y)
{
    printf("\x1B[%d;%dH*", y, x);
}

int main()
{
    int posx, posy;
    posx = 3, posy = 3;

    double angle = 0;
    int length = 0;


    while (angle < 360)
    {
        int y, x;

        x = cos(angle * PI / 180.0);
        if (x)
            length = -5;
        else
            length = 0;
        y = sin(angle * PI / 180.0);

        while (length < 5)
        {
            posx += x;
            posy += y;
            drawPoint(posx, posy);
            length++;
        }
        angle += 90;
    }

    printf("\x1B[10;0H");
    return 0;
}