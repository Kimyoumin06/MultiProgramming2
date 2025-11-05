#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHARACTERS 100

typedef struct {
    char name[50];
    int attack;
    int defense;
    int hp;
} Character;

int main(void)
{
    Character list[MAX_CHARACTERS];
    FILE* fp;
    char inputName[64];
    int inputNumber;
    int count = 0;

    // 1. 콘솔 입력
    printf("학번을 입력하세요: ");
    scanf_s("%d", &inputNumber);

    printf("이름을 입력하세요: ");
    scanf_s("%63s", inputName, (unsigned)_countof(inputName));

    // 2. Test.txt에 입력 내용 출력
    if (fopen_s(&fp, "Test.txt", "w") != 0 || fp == NULL) {
        printf("Test.txt 파일을 열 수 없습니다.\n");
        return 1;
    }

    fprintf(fp, "%d : %s\n", inputNumber, inputName);
    fclose(fp);

    // 3. students.csv 읽기
    if (fopen_s(&fp, "students.csv", "r") != 0 || fp == NULL) {
        printf("students.csv 파일을 열 수 없습니다.\n");
        return 1;
    }

    char line[256];
    while (fgets(line, sizeof(line), fp) != NULL && count < MAX_CHARACTERS) {
        line[strcspn(line, "\r\n")] = 0; // 개행 제거 (\r\n 처리)

        char* context = NULL; // strtok_s용 context
        char* token = strtok_s(line, ",", &context);
        if (!token) continue;
        strcpy_s(list[count].name, sizeof(list[count].name), token);

        token = strtok_s(NULL, ",", &context);
        if (!token) continue;
        list[count].attack = atoi(token);

        token = strtok_s(NULL, ",", &context);
        if (!token) continue;
        list[count].defense = atoi(token);

        token = strtok_s(NULL, ",", &context);
        if (!token) continue;
        list[count].hp = atoi(token);

        count++;
    }

    fclose(fp);

    // 4. Test.txt 이어쓰기
    if (fopen_s(&fp, "Test.txt", "a") != 0 || fp == NULL) {
        printf("Test.txt 파일을 열 수 없습니다.\n");
        return 1;
    }

    // (2) 가장 공격력 높은 사람
    int maxIndex = 0;
    for (int i = 1; i < count; i++) {
        if (list[i].attack > list[maxIndex].attack) {
            maxIndex = i;
        }
    }
    fprintf(fp, "가장 공격력이 높은 사람: %s (ATK=%d)\n", list[maxIndex].name, list[maxIndex].attack);

    // (3) 3번째 사람
    if (count >= 3) {
        fprintf(fp, "3번째: %s HP=%d\n", list[2].name, list[2].hp);
    }

    // (4) 8번째 사람
    if (count >= 8) {
        fprintf(fp, "8번째: %s HP=%d\n", list[7].name, list[7].hp);
    }

    // (5) 3번째 vs 8번째 전투
    if (count >= 8) {
        int hp3 = list[2].hp;
        int hp8 = list[7].hp;
        int damage3to8 = list[2].attack - list[7].defense;
        int damage8to3 = list[7].attack - list[2].defense;

        if (damage3to8 < 0) damage3to8 = 0;
        if (damage8to3 < 0) damage8to3 = 0;

        if (damage3to8 == 0 && damage8to3 == 0) {
            fprintf(fp, "3번째 vs 8번째: 무승부\n");
        }
        else {
            hp3 -= damage8to3;
            hp8 -= damage3to8;

            if (hp3 <= 0 && hp8 <= 0) {
                fprintf(fp, "3번째 vs 8번째: 무승부\n");
            }
            else if (hp3 <= 0) {
                fprintf(fp, "3번째 vs 8번째 승자: %s\n", list[7].name);
            }
            else if (hp8 <= 0) {
                fprintf(fp, "3번째 vs 8번째 승자: %s\n", list[2].name);
            }
            else {
                if (hp3 > hp8) {
                    fprintf(fp, "3번째 vs 8번째 승자: %s\n", list[2].name);
                }
                else if (hp8 > hp3) {
                    fprintf(fp, "3번째 vs 8번째 승자: %s\n", list[7].name);
                }
                else {
                    fprintf(fp, "3번째 vs 8번째: 무승부\n");
                }
            }
        }
    }

    // (6) 마지막 줄
    fprintf(fp, "교수님 시험문제 너무 쉽습니다. 담주에 더 어렵게 내주세요\n");

    fclose(fp);

    printf("Test.txt 생성 완료!\n");

    return 0;
}
