// Lecture08_Struct.cpp : �� ���Ͽ��� 'main' �Լ��� ���Ե˴ϴ�. �ű⼭ ���α׷� ������ ���۵ǰ� ����˴ϴ�.
//

#include <stdio.h>
#include <conio.h>

struct Fish
{
	char* name;

	char* talk;		//����Ⱑ ��� ��(���� + ����(������))
	int answer;		//��

	char* talk_O;	//�¾����� ���
	char* talk_X;	//Ʋ������ ���		
};


//����� 5�� ����� Fish �迭��.
int main()
{
	printf("� ������ (Y/N) >");
	char yn;
	yn = _getch();
	printf("%c\n", yn); //(500ms���� .�ϳ� ������)

	if (yn == 'Y' || yn == 'y')
	{

	}
	else if (yn == 'N' || yn == 'n')
	{

	}
	else
	{
		//�ݺ�;
	}

	//printf(".....\n"); //(500ms���� .�ϳ� ������)

	//printf("%s : " ������̸�, ����);	

	return 0;

}