#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#define MAX_CHARACTERS 100

typedef struct {
    char name[50];
    int attack;
    int defense;
    int hp;
    int mp;
} Character;

void clear_input_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main()
{
    Character list[MAX_CHARACTERS];
    FILE* fp;
    char inputName[64];
    int inputNumber;
    int count = 0;

    printf("학번을 입력하세요: ");
    if (scanf_s("%d", &inputNumber) != 1) {
        fprintf(stderr, "학번 입력 오류\n");
        return 1;
    }

    clear_input_buffer();

    printf("이름을 입력하세요: ");
    if (scanf_s("%63s", inputName, (unsigned)_countof(inputName)) != 1) {
        fprintf(stderr, "이름 입력 오류\n");
        return 1;
    }

    clear_input_buffer();

    if (fopen_s(&fp, "students.csv", "r") != 0 || fp == NULL) {
        printf("students.csv 파일을 열 수 없습니다.\n");
        return 1;
    }

    char line[256];

    while (fgets(line, sizeof(line), fp) != NULL && count < MAX_CHARACTERS) {
        
        size_t len = strlen(line);
        
        while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r')) {
            line[len - 1] = '\0';
            len--;
        }

        if (len == 0) continue;

        char* context = NULL;
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

        if (!token) continue;
        list[count].mp = atoi(token);
        
        count++;
    }

    fclose(fp);

    if (fopen_s(&fp, "Test.txt", "w") != 0 || fp == NULL) {
        printf("Test.txt 파일을 열 수 없습니다.\n");
        return 1;
    }

    fprintf(fp, "%d : %s\n", inputNumber, inputName);

    if (count == 0) {
        printf("학생 데이터가 없습니다.\n");
        fprintf(fp, "학생 데이터가 없습니다.\n");
        fclose(fp);
        return 1;
    }

    fprintf(fp, "%s %s\n", list[6], list[7]);

    int maxIndex = 0;
    for (int i = 1; i < count; i++) {
        if (list[i].attack > list[maxIndex].attack) {
            maxIndex = i;
        }
    }

    if (count >= 8) {
        int hp4 = list[3].hp;
        int hp8 = list[7].hp;
        // 각각 3번째와 8번째 캐릭터의 체력을 hp3, hp8에 저장함.

        int damage4to8 = list[3].attack - list[7].defense;
        int damage8to4 = list[7].attack - list[3].defense;
        // damage3to8 = 8번째 캐릭터가 받는 데미지.
        // damage8to3 = 3번째 캐릭터가 받는 데미지.
        

        if (damage4to8 < 0) damage4to8 = 0;
        if (damage8to4 < 0) damage8to4 = 0;
        // 받은 피해가 0보다 작을 경우 해당 값을 0으로 처리함.

        if (damage4to8 == 0 && damage8to4 == 0) {
            fprintf(fp, "3번째 vs 8번째: 무승부\n");
        }
        // 둘 다 받은 피해가 0일 경우 무승부 처리.

        else {
            while (hp4 > 0 && hp8 > 0) {
                hp4 -= damage8to4;
                hp8 -= damage4to8;
            }

            if (hp4 <= 0 && hp8 <= 0) {
                fprintf(fp, "3번째 vs 8번째: 무승부\n");
            }
            else if (hp4 <= 0) {
                fprintf(fp, "3번째 vs 8번째 승자: %s\n", list[7].name); // 3번째 사망 (8번째 승리)
            }
            else if (hp8 <= 0) {
                fprintf(fp, "3번째 vs 8번째 승자: %s\n", list[3].name); // 8번째 사망 (3번째 승리)
            }
        }
    }

    fprintf(fp, "\n\n\n%s%s%s\n", list[8], list[9], list[10]);

    int AverageAtk = (list[0].attack + list[1].attack + list[2].attack + list[3].attack + list[4].attack +
        list[5].attack + list[6].attack + list[7].attack + list[8].attack + list[9].attack + list[10].attack) / 10;
    int AverageDef = (list[0].defense + list[1].defense + list[2].defense + list[3].defense + list[4].defense +
        list[5].defense + list[6].defense + list[7].defense + list[8].defense + list[9].defense + list[10].defense) / 11;;

    fprintf(fp, "Average atk: %d\nAverage def: %d\n", AverageAtk, AverageDef);

    fprintf(fp, "교수님 시험문제 너무 쉽습니다. 담주에 더 어렵게 내주세요.\n");

    fclose(fp);
    return 0;
}