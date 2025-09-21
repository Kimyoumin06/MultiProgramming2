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
    double angle = 180;  // 시작 각도

    int times = 12;      // 회전 횟수
    int length = 2;      // 각 구간 이동 횟수
    int printtimes = 2;  // 현재 구간에서 몇 번 찍을지

    double x = 0, y = 0;

    moveCursor(posX, posY);

    while (times > 0)
    {
        // 방향 결정
        if (angle == 180) angle = 90;
        else if (angle == 90) angle = 0;
        else if (angle == 0) angle = 270;
        else if (angle == 270) angle = 180;

        // 방향 벡터 계산
        x = cos(angle * PI / 180.0);
        y = sin(angle * PI / 180.0);

        // 해당 방향으로 printtimes번 이동
        for (int i = 0; i < printtimes; i++)
        {
            posX += (int)x;
            posY -= (int)y;  // 콘솔 좌표계 때문에 y는 반대
            moveCursor(posX, posY);
            printf("#");
        }

        // 다음 이동 준비
        length += 2;           // 이동 길이 2 증가
        printtimes = length;   // 다음 구간 이동 횟수 갱신
        times--;               // 남은 구간 횟수 감소
    }

    moveCursor(10, 20);
    return 0;
}
