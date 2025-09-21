#include <stdio.h>

#include <math.h>

#include <Windows.h>



#define PI 3.14159226535897



void moveCursor(int x, int y)

{

	printf("\x1b[%d;%dH", y, x);

}



//매개변수 isExploded

//0: 폭발전 폭탄

//1: 폭발함

void printBomb(int isExploded)

{

	//폭탄은 항상 7칸

	if (isExploded)

	{

		printf("\x1b[A^^^^^^^");

		printf("\x1b[B\x1b[7D!!BAM!!");

		printf("\x1b[B\x1b[7D^^^^^^^");

	}

	else

		printf("(  b  )");

}



int main()

{

	// 여기부터 코드를 작성하세요----------------------   

	printBomb(0);

	// 8,0이 폭탄 바로 옆

	int posX = 14, posY = 9;

	int angle = 180;



	int times = 12;

	int length = 2;

	int printtimes = 2;



	int x, y;



	moveCursor(posX, posY);



	while (times)

	{



		//90 -> 0 -> 270 -> 180

		if (angle == 180)

		{

			angle = 90;

		}

		else if (angle == 90)

		{

			angle = 0;

		}

		else if (angle == 0)

		{

			angle = 270;

		}

		else if (angle == 270)

		{

			angle = 180;





			x = cos(angle * PI / 180.0);

			y = sin(angle * PI / 180.0);



			while (printtimes)

			{

				posX += x;

				posY += y;

				moveCursor(posX, posY);

				printf("#");

				printtimes--;

			}

			length = length + 2;

			printtimes = length;

			times--;

		}

	}

	// 여기까지 코드를 작성하세요----------------------   

	moveCursor(10, 20);

	return 0;

}