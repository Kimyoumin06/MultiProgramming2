#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

struct Fish
{
	char *name;

	char *talk;
	int answer;

	char* talk_O;
	char* talk_X;
};

int main()
{
	struct Fish fishes[5] = {
		{"스펀지", "스펀지가 모티브인 캐릭터는?\n1.스폰지밥 2.징징이 3.집게사장 4.다람이", 1,"정답","틀림"},
		{"별가사리", "별가사리가 모티브인 캐릭터는?\n1.스폰지밥 2.뚱이 3.집게사장 4.다람이", 2,"정답","틀림"},
		{"오징어", "오징어가 모티브인 캐릭터는?\n1.스폰지밥 2.징징이 3.집게사장 4.다람이", 2,"정답","틀림"},
		{"게", "게가 모티브인 캐릭터는?\n1.스폰지밥 2.징징이 3.집게사장 4.다람이", 3,"정답","틀림"},
		{"다람쥐", "다람쥐가 모티브인 캐릭터는?\n1.스폰지밥 2.징징이 3.집게사장 4.다람이", 4,"정답","틀림"},
	};

	int i = 0;
	int fishing = 1;
	int waiting = 5;
	int Answer;

	int O = 0;
	int X = 0;

	while (fishing)
	{

		printf("찌를 던진다 (Y/N) >");
		char yn;
		yn = _getch();
		printf("%c\n", yn);

		if (yn == 'y' || yn == 'Y')
		{
			system("cls");
			printf("당신은 찌를 던졌다!\n");
			while (waiting)
			{
				Sleep(500);
				printf(".");
				waiting--;
			}
			printf("\n입질이 왔다!!");
			
			srand((unsigned int)time(NULL));
			int idx = rand() % 5;

			printf("오늘의 물고기 퀴즈!\n");
			printf("%s : %s\n", fishes[idx].name, fishes[idx].talk);

			Answer = _getch();
			if (Answer - '0' == fishes[idx].answer)
			{
				printf("%s\n", fishes[idx].talk_O);
				O++;
			}
			else
			{
				printf("%s\n", fishes[idx].talk_X);
				X++;
			}
		}

		else if (yn == 'n' || yn == 'N')
		{
			printf("당신은 낚시를 관두었다..");
			fishing--;
		}

		else
		{
			printf("실수로 미끼를 놓쳤다.. 다시 시도하자..\n");
		}

	}

	//printf(".....\n"); //(500ms마다 .하나 찍히게)

	//printf("%s : " , fishes[i]);

	return 0;
}