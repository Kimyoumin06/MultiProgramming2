#include <stdio.h>
#include <windows.h>

// 조건 : printf 한 번만 쓰고 #으로 6x5 사이즈로 네모 만들기

int square()
{
	int x = 0, y = 0;
	int w = 0, s = 0;
	int time = 5;

	while (y<5)
	{
		while (x<6)
		{
			if (y == 0 || y == 4 || x == 0 || x == 5)
			{
				printf("\x1B[%d;%dH#", y + 1, x + 1);
			}
			x++;
		}
		y++;
	}
}

int main()
{
	square();
	return 0;
}