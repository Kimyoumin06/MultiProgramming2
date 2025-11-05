#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h> // <conio.h>는 허용 헤더에 포함되어 있으나, 이 코드에서는 사용하지 않습니다.

#define MAX_CHARACTERS 100 // 최대 캐릭터 수

typedef struct {
    char name[50];
    int attack;
    int defense;
    int hp;
} Character;

// 입력 버퍼를 비우는 함수: scanf_s("%d", ...) 후 남은 개행 문자 제거 목적
void clear_input_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main(void)
{
    Character list[MAX_CHARACTERS];
    FILE* fp;
    char inputName[64];
    int inputNumber;
    int count = 0;

    // 1. 콘솔 입력 (CRT 보안 함수 사용)
    printf("학번을 입력하세요: ");
    if (scanf_s("%d", &inputNumber) != 1) {
        fprintf(stderr, "학번 입력 오류\n");
        return 1;
    }
    // 정수 입력 후 입력 버퍼 비우기
    clear_input_buffer();

    printf("이름을 입력하세요: ");
    if (scanf_s("%63s", inputName, (unsigned)_countof(inputName)) != 1) {
        fprintf(stderr, "이름 입력 오류\n");
        return 1;
    }
    // 이름 입력 후 입력 버퍼 비우기
    clear_input_buffer();

    // 2. students.csv 읽기 (CRT 보안 함수 사용)
    if (fopen_s(&fp, "students.csv", "r") != 0 || fp == NULL) {
        printf("students.csv 파일을 열 수 없습니다.\n");
        return 1;
    }

    char line[256];

    // [수정된 부분]
    // CSV 파일의 첫 번째 줄(헤더)을 읽어서 버립니다.
    // 이렇게 하면 while 루프는 실제 학생 데이터(두 번째 줄)부터 읽기 시작합니다.
    if (fgets(line, sizeof(line), fp) == NULL) {
        printf("students.csv 파일이 비어있거나 헤더를 읽을 수 없습니다.\n");
        fclose(fp);
        return 1;
    }

    while (fgets(line, sizeof(line), fp) != NULL && count < MAX_CHARACTERS) {
        // 줄바꿈 문자('\n', '\r') 제거 로직
        size_t len = strlen(line);
        while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r')) {
            line[len - 1] = '\0';
            len--;
        }

        // 빈 줄은 건너뜁니다.
        if (len == 0) continue;

        // CSV 토큰 분리 및 데이터 저장 (CRT 보안 함수 사용)
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

        count++;
    }
    fclose(fp);

    // 3. Test.txt에 출력 (w 모드, CRT 보안 함수 사용)
    if (fopen_s(&fp, "Test.txt", "w") != 0 || fp == NULL) {
        printf("Test.txt 파일을 열 수 없습니다.\n");
        return 1;
    }

    // (1) 학번과 이름
    fprintf(fp, "%d : %s\n", inputNumber, inputName);

    // (2) 가장 공격력 높은 사람 찾기 (먼저 등장한 사람 우선)
    // count가 0이 아닌지 확인
    if (count == 0) {
        printf("학생 데이터가 없습니다.\n");
        fprintf(fp, "학생 데이터가 없습니다.\n");
        fclose(fp);
        return 1;
    }

    int maxIndex = 0;
    for (int i = 1; i < count; i++) {
        if (list[i].attack > list[maxIndex].attack) {
            maxIndex = i;
        }
    }
    fprintf(fp, "가장 공격력이 높은 사람: %s (ATK=%d)\n", list[maxIndex].name, list[maxIndex].attack);

    // (3) 3번째 사람 (인덱스 2)
    // 헤더를 건너뛰었으므로 list[2]가 3번째 학생입니다.
    if (count >= 3) {
        fprintf(fp, "3번째: %s HP=%d\n", list[2].name, list[2].hp);
    }

    // (4) 8번째 사람 (인덱스 7)
    // 헤더를 건너뛰었으므로 list[7]이 8번째 학생입니다.
    if (count >= 8) {
        fprintf(fp, "8번째: %s HP=%d\n", list[7].name, list[7].hp);
    }

    // (5) 3번째 vs 8번째 전투 (전투 규칙 완벽 반영)
    if (count >= 8) {
        int hp3 = list[2].hp;
        int hp8 = list[7].hp;

        // 피해 계산식: 받는 피해 = max(0, 상대방 공격력 - 자신의 방어력)
        int damage3to8 = list[2].attack - list[7].defense;
        int damage8to3 = list[7].attack - list[2].defense;

        if (damage3to8 < 0) damage3to8 = 0;
        if (damage8to3 < 0) damage8to3 = 0;

        // 양쪽 피해가 0이면 즉시 무승부 처리
        if (damage3to8 == 0 && damage8to3 == 0) {
            fprintf(fp, "3번째 vs 8번째: 무승부\n");
        }
        else {
            // [수정된 로직]
            // HP가 둘 다 0보다 클 동안 전투를 반복합니다.
            while (hp3 > 0 && hp8 > 0) {
                // 두 사람은 동시에 서로 피해를 입는다.
                hp3 -= damage8to3;
                hp8 -= damage3to8;
            }

            // 루프가 종료된 후(즉, 누군가 HP가 0 이하가 된 후) 승패 판정
            // (같은 턴에 둘 다 0 이하면 무승부)
            if (hp3 <= 0 && hp8 <= 0) {
                fprintf(fp, "3번째 vs 8번째: 무승부\n"); // 둘 다 사망
            }
            else if (hp3 <= 0) {
                fprintf(fp, "3번째 vs 8번째 승자: %s\n", list[7].name); // 3번째 사망 (8번째 승리)
            }
            else if (hp8 <= 0) {
                fprintf(fp, "3번째 vs 8번째 승자: %s\n", list[2].name); // 8번째 사망 (3번째 승리)
            }
            // 한 턴에 승부가 나지 않아도 무승부 처리하던 기존 'else' 블록을 제거했습니다.
        }
    }

    // (6) 마지막 줄
    fprintf(fp, "교수님 시험문제 너무 쉽습니다. 담주에 더 어렵게 내주세요\n");

    fclose(fp);

    return 0;
}