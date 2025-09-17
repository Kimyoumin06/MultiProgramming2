#include<math.h>
#include<stdio.h>
#include<Windows.h>

#define PI 3.14159265358979323846

void gotoxy(int x, int y) {
	printf("\033[%d;%dH", y, x);
}

int main() {
	int startX = 5, startY = 5;
	gotoxy(startX, startY);
	printf("(Bomb)");

	int posX = startX + 5, posY = startY;
	int dx, dy;
	double angle = 0.0;
	int length = 5;
	while (length > 0)
	{
		dx = cos(angle * PI / 180.0);
		dy = sin(angle * PI / 180.0);
		int count = 0;
		while (count < length)
		{
			posX += dx;
			posY += dy;
			gotoxy(posX, posY);
			if (count == length - 1) printf("+");
			else printf("-");
			count++;
		}
		angle += 90.0;
		dx = cos(angle * PI / 180.0);
		dy = sin(angle * PI / 180.0);
		length--;
		count = 0;
		while (count < length)
		{
			posX += dx;
			posY += dy;
			gotoxy(posX, posY);
			if (count == length - 1) printf("+");
			else printf("|");
			count++;
		}
		angle += 90.0;
	}//도화선 그리기

	gotoxy(posX, posY);
	printf("*");

	angle -= 180.0;

	while (length < 5) {
		angle -= 90.0;
		dx = cos(angle * PI / 180.0);
		dy = sin(angle * PI / 180.0);
		int count = 0;
		while (count < length)
		{
			Sleep(100);
			gotoxy(posX, posY);
			printf(" ");
			posX += dx;
			posY += dy;
			gotoxy(posX, posY);
			printf("*");
			count++;
		}
		angle -= 90.0;
		dx = cos(angle * PI / 180.0);
		dy = sin(angle * PI / 180.0);
		length++;
		count = 0;
		while (count < length)
		{
			Sleep(100);
			gotoxy(posX, posY);
			printf(" ");
			posX += dx;
			posY += dy;
			gotoxy(posX, posY);
			if (length != 5) printf("*");
			count++;
		}
	}
	gotoxy(startX, startY - 1);
	printf("^^^^^^");
	gotoxy(startX, startY);
	printf("!BOOM!");
	gotoxy(startX, startY + 1);
	printf("^^^^^^");

	gotoxy(0, startY + 10);
	return 0;
}