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

int max_int(int a, int b) {
    return (a > b) ? a : b;
}

int simulate_fight(Character c1_original, Character c2_original) {
    Character c1 = c1_original;
    Character c2 = c2_original;

    int max_turns = 100000;

    for (int turn = 0; turn < max_turns; turn++) {
        int damage_c1_to_c2 = 0;
        int damage_c2_to_c1 = 0;

        if (c1.mp >= c1.attack) {
            c1.mp -= c1.attack;
            damage_c1_to_c2 = c1.attack;
        }
        else {
            c1.mp += 10;
            damage_c1_to_c2 = c1.attack / 2;
        }

        if (c2.mp >= c2.attack) {
            c2.mp -= c2.attack;
            damage_c2_to_c1 = c2.attack;
        }
        else {
            c2.mp += 10;
            damage_c2_to_c1 = c2.attack / 2;
        }

        int final_damage_c1_to_c2 = max_int(0, damage_c1_to_c2 - c2.defense);
        int final_damage_c2_to_c1 = max_int(0, damage_c2_to_c1 - c1.defense);

        if (turn == 0 && final_damage_c1_to_c2 == 0 && final_damage_c2_to_c1 == 0) {
            return 0;
        }

        c1.hp -= final_damage_c2_to_c1;
        c2.hp -= final_damage_c1_to_c2;

        int c1_died = (c1.hp <= 0);
        int c2_died = (c2.hp <= 0);

        if (c1_died && c2_died) {
            return 0;
        }
        else if (c1_died) {
            return 2;
        }
        else if (c2_died) {
            return 1;
        }
    }

    return 0;
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

    if (fgets(line, sizeof(line), fp) == NULL) {
        printf("students.csv 파일이 비어있거나 헤더를 읽을 수 없습니다.\n");
        fclose(fp);
        return 1;
    }

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
        token = strtok_s(NULL, ",", &context);

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

    fprintf(fp, "%s %s\n", list[6].name, list[7].name);

    if (count >= 8) {
        Character mother = list[6];
        Character horo = list[2];

        int result = simulate_fight(mother, horo);

        if (result == 1) {
            fprintf(fp, "%s 승! , %s 패\n", mother.name, horo.name);
        }
        else if (result == 2) {
            fprintf(fp, "%s 승! , %s 패\n", horo.name, mother.name);
        }
        else {
            fprintf(fp, "무승부\n");
        }
    }
    else {
        fprintf(fp, "전투 시뮬레이션 데이터 부족\n");
    }

    if (count > 0) {
        Character mother_ref = list[6];
        int first_winner = 1;
        int winner_count = 0;

        char winners[1024] = "";

        for (int i = 0; i < count; i++) {
            if (i == 6) continue;

            int result = simulate_fight(list[i], mother_ref);

            if (result == 1) {
                winner_count++;

                if (!first_winner) {
                    strcat_s(winners, sizeof(winners), ", ");
                }
                strcat_s(winners, sizeof(winners), list[i].name);
                first_winner = 0;
            }
        }

        if (winner_count > 0) {
            fprintf(fp, "%s 승!\n", winners);
        }
        else {
            fprintf(fp, "%s 승!\n", mother_ref.name);
        }

    }
    else {
        fprintf(fp, "데이터 부족으로 Mother의 승리자를 판별할 수 없습니다.\n");
    }

    fprintf(fp, "%s%s%s\n", list[8].name, list[9].name, list[10].name);

    int AverageAtk = (list[0].attack + list[1].attack + list[2].attack + list[3].attack + list[4].attack +
        list[5].attack + list[6].attack + list[7].attack + list[8].attack + list[9].attack + list[10].attack) / 11;
    int AverageDef = (list[0].defense + list[1].defense + list[2].defense + list[3].defense + list[4].defense +
        list[5].defense + list[6].defense + list[7].defense + list[8].defense + list[9].defense + list[10].defense) / 11;;

    fprintf(fp, "Average atk: %d\nAverage def: %d\n", AverageAtk, AverageDef);

    fprintf(fp, "교수님 시험문제 너무 쉽습니다. 담주에 더 어렵게 내주세요.\n");

    fclose(fp);
    return 0;
}