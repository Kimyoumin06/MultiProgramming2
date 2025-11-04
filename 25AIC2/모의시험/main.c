#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[64];
    int atk;
    int def;
    int hp;
} Student;

int max(int a, int b) {
    return (a > b) ? a : b;
}

int main(void) {
    FILE* fp;
    char line[256];
    char student_name[64];
    int student_number;
    Student students[10];  // 총 10명
    int count = 0;

    // 1. 사용자 입력
    printf("학번을 입력하세요: ");
    scanf_s("%d", &student_number);

    printf("이름을 입력하세요: ");
    scanf_s("%63s", student_name, (unsigned)_countof(student_name));

    // 2. students.csv 읽기
    if (fopen_s(&fp, "students.csv", "r") != 0 || fp == NULL) {
        printf("students.csv 파일 열기 실패!\n");
        return 1;
    }

    // 헤더 읽기
    if (fgets(line, sizeof(line), fp) == NULL) {
        printf("CSV 헤더 읽기 실패!\n");
        fclose(fp);
        return 1;
    }

    while (fgets(line, sizeof(line), fp) != NULL && count < 10) {
        line[strcspn(line, "\n")] = 0; // 개행 제거

        char* token = strtok(line, ",");
        if (token == NULL) continue;
        strcpy_s(students[count].name, sizeof(students[count].name), token);

        token = strtok(NULL, ",");
        if (token == NULL) continue;
        students[count].atk = atoi(token);

        token = strtok(NULL, ",");
        if (token == NULL) continue;
        students[count].def = atoi(token);

        token = strtok(NULL, ",");
        if (token == NULL) continue;
        students[count].hp = atoi(token);

        count++;
    }
    fclose(fp);

    // 3. Test.txt에 출력
    if (fopen_s(&fp, "Test.txt", "w") != 0 || fp == NULL) {
        printf("Test.txt 열기 실패!\n");
        return 1;
    }

    // (1) 사용자 정보
    fprintf_s(fp, "%d : %s\n", student_number, student_name);

    // (2) 가장 공격력이 높은 사람
    int maxAtkIndex = 0;
    for (int i = 1; i < count; i++) {
        if (students[i].atk > students[maxAtkIndex].atk) {
            maxAtkIndex = i;
        }
    }
    fprintf_s(fp, "가장 공격력이 높은 사람: %s (ATK=%d)\n",
        students[maxAtkIndex].name, students[maxAtkIndex].atk);

    // (3) 3번째 사람
    fprintf_s(fp, "3번째: %s HP=%d\n", students[2].name, students[2].hp);

    // (4) 8번째 사람
    fprintf_s(fp, "8번째: %s HP=%d\n", students[7].name, students[7].hp);

    // (5) 3번째 vs 8번째 전투
    int damage3to8 = max(0, students[2].atk - students[7].def);
    int damage8to3 = max(0, students[7].atk - students[2].def);

    int hp3 = students[2].hp;
    int hp8 = students[7].hp;

    while (1) {
        hp3 -= damage8to3;
        hp8 -= damage3to8;

        if (hp3 <= 0 && hp8 <= 0) {
            fprintf_s(fp, "3번째 vs 8번째: 무승부\n");
            break;
        }
        else if (hp3 <= 0) {
            fprintf_s(fp, "3번째 vs 8번째 승자: %s\n", students[7].name);
            break;
        }
        else if (hp8 <= 0) {
            fprintf_s(fp, "3번째 vs 8번째 승자: %s\n", students[2].name);
            break;
        }

        if (damage3to8 == 0 && damage8to3 == 0) {
            fprintf_s(fp, "3번째 vs 8번째: 무승부\n");
            break;
        }
    }

    // (6) 마지막 줄
    fprintf_s(fp, "교수님 시험문제 너무 쉽습니다. 담주에 더 어렵게 내주세요\n");

    fclose(fp);

    printf("Test.txt 생성 완료!\n");
    return 0;
}
