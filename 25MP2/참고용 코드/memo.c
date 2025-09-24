#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define Key_a 97
#define Key_z 122
#define NUM (Key_z - Key_a + 1)

// 문자 교환 함수
void swap(char* a, char* b)
{
    char c = *a;
    *a = *b;
    *b = c;
}

// 간단한 버블 정렬 (알파벳 오름차순)
void bubble_sort(char arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

int main()
{
    char random[NUM];
    char sorted[NUM];
    int i;

    srand(time(NULL));  // 랜덤 시드 초기화

    // 1) 배열 초기화 (0으로)
    for (i = 0; i < NUM; i++)
    {
        random[i] = 0;
    }

    // 2) 무작위로 알파벳 a~z 채우기
    for (i = 0; i < NUM; i++)
    {
        while (1)
        {
            int rand_index = rand() % NUM;
            if (random[rand_index] == 0)
            {
                random[rand_index] = (char)(i + Key_a);
                break;
            }
        }
    }

    // 3) 복사본 만들기 (정렬용)
    for (i = 0; i < NUM; i++)
    {
        sorted[i] = random[i];
    }

    // 4) 정렬 (알파벳 오름차순)
    bubble_sort(sorted, NUM);

    // 5) 출력: 인덱스, 랜덤 배열, 정렬된 배열 (더블 소팅 결과 비교)
    printf("Index\tRandom\tSorted\n");
    for (i = 0; i < NUM; i++)
    {
        printf("%2d\t  %c\t   %c\n", i, random[i], sorted[i]);
    }

    return 0;
}
