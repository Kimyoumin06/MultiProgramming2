#include <stdio.h>
#include <stdlib.h>

#define NUM 10000

int main()
{
    //������ ���� ���ϱ�
    int r_value = rand() % NUM;

    int random[NUM];
    int index[NUM];

    //-----------�ʱ�ȭ-------------------------
    int i;
    for (i = 0; i < NUM; i++)
    {
        random[i] = -1;
        index[i] = -1;
    }

    //------------�����ϰ� ���� �ֱ�------------------------
    for (i = 0; i < NUM; i++)
    {
        while (1)
        {
            int rand_index = rand() % NUM;
            if (random[rand_index] == -1)
            {
                random[rand_index] = i;
                break;
            }
        }
    }

    //------------������� ���� ����------------------------
    for (i = 0; i < NUM; i++)
    {
        index[random[i]] = i;
    }

    printf("\t\trand\tind");
    for (i = 0; i < NUM; i++)
    {
        printf("\n\t%d\t%d\t%d", i, random[i], index[i]);
    }










    return 0;
}