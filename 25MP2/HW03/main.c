#include <stdio.h>
#include <math.h>
#include <Windows.h>

#define PI 3.14159226535897

void moveCursor(int x, int y)
{
    printf("\x1b[%d;%dH", y, x);
}

//�Ű����� isExploded
//0: ������ ��ź
//1: ������
void printBomb(int isExploded)
{
    //��ź�� �׻� 7ĭ
    if (isExploded)
    {
        printf("\x1b[A^^^^^^^");
        printf("\x1b[B\x1b[7D!!BAM!!");
        printf("\x1b[B\x1b[7D^^^^^^^");
    }
    else
        printf("(  b  )");
}

int main()
{
    // ������� �ڵ带 �ۼ��ϼ���----------------------   
    printBomb(0);
    // 8,0�� ��ź �ٷ� ��
    int posX = 14, posY = 9;
    double angle = 90.0;

    int length = 0;
    int count = 2;

    int x, y;

    moveCursor(posX, posY);

    while (length <= 12)
    {
        x = cos(angle * PI / 180.0);
        y = sin(angle * PI / 180.0);

        posX += x;
        posY += y;

        moveCursor(posX, posY);

        length++;
        if (length % count == 0)
        {
            angle += 90.0;
            printf("*");
        }
    }



    // ������� �ڵ带 �ۼ��ϼ���----------------------   
    moveCursor(10, 20);
    return 0;
}