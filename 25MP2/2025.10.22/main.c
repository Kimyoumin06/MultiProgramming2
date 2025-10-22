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
		{"������", "�������� ��Ƽ���� ĳ���ʹ�?\n1.�������� 2.¡¡�� 3.���Ի��� 4.�ٶ���", 1,"����","Ʋ��"},
		{"�����縮", "�����縮�� ��Ƽ���� ĳ���ʹ�?\n1.�������� 2.���� 3.���Ի��� 4.�ٶ���", 2,"����","Ʋ��"},
		{"��¡��", "��¡� ��Ƽ���� ĳ���ʹ�?\n1.�������� 2.¡¡�� 3.���Ի��� 4.�ٶ���", 2,"����","Ʋ��"},
		{"��", "�԰� ��Ƽ���� ĳ���ʹ�?\n1.�������� 2.¡¡�� 3.���Ի��� 4.�ٶ���", 3,"����","Ʋ��"},
		{"�ٶ���", "�ٶ��㰡 ��Ƽ���� ĳ���ʹ�?\n1.�������� 2.¡¡�� 3.���Ի��� 4.�ٶ���", 4,"����","Ʋ��"},
	};

	int i = 0;
	int fishing = 1;
	int waiting = 5;
	int Answer;

	int O = 0;
	int X = 0;

	while (fishing)
	{

		printf("� ������ (Y/N) >");
		char yn;
		yn = _getch();
		printf("%c\n", yn);

		if (yn == 'y' || yn == 'Y')
		{
			system("cls");
			printf("����� � ������!\n");
			while (waiting)
			{
				Sleep(500);
				printf(".");
				waiting--;
			}
			printf("\n������ �Դ�!!");
			
			srand((unsigned int)time(NULL));
			int idx = rand() % 5;

			printf("������ ����� ����!\n");
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
			printf("����� ���ø� ���ξ���..");
			fishing--;
		}

		else
		{
			printf("�Ǽ��� �̳��� ���ƴ�.. �ٽ� �õ�����..\n");
		}

	}

	//printf(".....\n"); //(500ms���� .�ϳ� ������)

	//printf("%s : " , fishes[i]);

	return 0;
}