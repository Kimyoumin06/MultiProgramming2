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
    // ��ź ���
    moveCursor(0, 0);
    printBomb(0);

    // �Ҳ� ���� ��ġ
    int posX = 14, posY = 9;
    moveCursor(posX, posY);
    printf("*");

    // ���� ��ü �׸���
    int cx = posX, cy = posY;
    int length = 2;
    int dir = 0;       // 0:��, 1:��, 2:��, 3:�� (�ݽð�)
    int times = 12;

    for (int count = 0; count < times; count++)
    {
        for (int i = 2; i < length; i++)
        {
            if (dir == 0) cy++;       // ��
            else if (dir == 1) cx++;  // ��
            else if (dir == 2) cy--;  // ��
            else if (dir == 3) cx--;  // ��

            moveCursor(cx, cy);
            printf("#");
        }

        dir++;
        if (dir == 4) dir = 0;

        if (count % 2 == 1) length = length + 3;
    }

    // �Ҳ� �̵�
    cx = posX; cy = posY;
    length = 2;
    dir = 0;

    for (int count = 0; count < times; count++)
    {
        for (int i = 2; i < length; i++)
        {
            // ���� ��ġ ����
            moveCursor(cx, cy);
            printf(" ");

            if (dir == 0) cy++;       // ��
            else if (dir == 1) cx++;  // ��
            else if (dir == 2) cy--;  // ��
            else if (dir == 3) cx--;  // ��

            moveCursor(cx, cy);
            Sleep(200);
            printf("*");
        }

        dir++;
        if (dir == 4) dir = 0;

        if (count % 2 == 1) length = length + 3;
    }

    // ����
    moveCursor(0, 0);
    printBomb(1);

    moveCursor(0, 20);
    return 0;
}
