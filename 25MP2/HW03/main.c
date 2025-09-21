#include <stdio.h>
#include <Windows.h>

void moveCursor(int x, int y)
{
    printf("\x1b[%d;%dH", y, x);
}

void printBomb(int isExploded)
{
    if (isExploded)
    {
        printf("\x1b[A^^^^^^^");
        printf("\x1b[B\x1b[7D!!BAM!!");
        printf("\x1b[B\x1b[7D^^^^^^^");
    }
    else
        printf("(  B  )");
}

int main()
{

    // 여기부터 코드를 작성하세요----------------------  

    moveCursor(0, 3);
    printBomb(0);

    int posX = 14, posY = 9;

    int dx[4] = { 0, 1, 0, -1 };
    int dy[4] = { 1, 0, -1, 0 };

    int dir = 0;
    int length = 2;
    int repeat = 0;
    int times = 12;

    while (times--)
    {
        for (int i = 0; i < length; i++)
        {
            posX += dx[dir];
            posY += dy[dir];
            moveCursor(posX, posY);
            printf("#");
        }

        dir = (dir + 1) % 4;
        repeat++;

        if (repeat == 2)
        {
            length += 2;
            repeat = 0;
        }
    }

    times = 12;
    dir = 0;
    repeat = 0;
    length = 2;
    posX = 14, posY = 9;

    while (times--)
    {
        for (int i = 0; i < length; i++)
        {
            posX += dx[dir];
            posY += dy[dir];
            moveCursor(posX, posY);
            printf("*");
            Sleep(200);
            moveCursor(posX, posY);
            printf(" ");
        }

        dir = (dir + 1) % 4;
        repeat++;

        if (repeat == 2)
        {
            length += 2;
            repeat = 0;
        }
    }

    system("cls");
    moveCursor(0, 3);
    printBomb(1);

    // 여기까지 코드를 작성하세요----------------------  
    moveCursor(10, 20);
    return 0;
}
