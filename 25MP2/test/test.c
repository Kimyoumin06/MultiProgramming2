#include <stdio.h>
#include <math.h>
#include <Windows.h>

#define PI 3.14159226535897

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
        printf("(  b  )");
}

int main()
{
    printBomb(0);

    int posX = 14, posY = 9;
    double angle = 180;  // ���� ����

    int times = 12;      // ȸ�� Ƚ��
    int length = 2;      // �� ���� �̵� Ƚ��
    int printtimes = 2;  // ���� �������� �� �� ������

    double x = 0, y = 0;

    moveCursor(posX, posY);

    while (times > 0)
    {
        // ���� ����
        if (angle == 180) angle = 90;
        else if (angle == 90) angle = 0;
        else if (angle == 0) angle = 270;
        else if (angle == 270) angle = 180;

        // ���� ���� ���
        x = cos(angle * PI / 180.0);
        y = sin(angle * PI / 180.0);

        // �ش� �������� printtimes�� �̵�
        for (int i = 0; i < printtimes; i++)
        {
            posX += (int)x;
            posY -= (int)y;  // �ܼ� ��ǥ�� ������ y�� �ݴ�
            moveCursor(posX, posY);
            printf("#");
        }

        // ���� �̵� �غ�
        length += 2;           // �̵� ���� 2 ����
        printtimes = length;   // ���� ���� �̵� Ƚ�� ����
        times--;               // ���� ���� Ƚ�� ����
    }

    moveCursor(10, 20);
    return 0;
}
