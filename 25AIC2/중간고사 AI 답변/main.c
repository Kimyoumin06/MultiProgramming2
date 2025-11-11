#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h> // Though generally specific to older Windows/MSVC, kept as requested.

// 최대 캐릭터 수 정의
#define MAX_CHARACTERS 100
// 이름 최대 길이 정의
#define MAX_NAME_LEN 50

// Character 구조체 정의
typedef struct {
    char name[MAX_NAME_LEN];
    int attack;
    int defense;
    int hp;
    int mp;
} Character;

// 입력 버퍼를 비우는 함수 (scanf_s 사용 후 필요)
void clear_input_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// 두 정수 중 큰 값을 반환하는 함수 (max() 대체)
int max_int(int a, int b) {
    return (a > b) ? a : b;
}

/**
 * @brief 캐릭터 A와 B 간의 전투를 시뮬레이션합니다.
 *
 * @param c1_original 첫 번째 캐릭터 (공격자)
 * @param c2_original 두 번째 캐릭터 (방어자)
 * @return int 1: c1 승리, 2: c2 승리, 0: 무승부
 */
int simulate_fight(Character c1_original, Character c2_original) {
    // 전투 중 HP/MP 변화를 위해 캐릭터 복사본 사용
    Character c1 = c1_original;
    Character c2 = c2_original;

    int max_turns = 10000; // 무한 루프 방지를 위한 안전 장치

    // 전투 시작
    for (int turn = 0; turn < max_turns; turn++) {
        int damage_c1_to_c2 = 0;
        int damage_c2_to_c1 = 0;

        // --- C1의 행동 (C2에게 가하는 피해 계산) ---
        if (c1.mp >= c1.attack) {
            // MP가 ATK 이상: MP 소모, ATK만큼 피해
            c1.mp -= c1.attack;
            damage_c1_to_c2 = c1.attack;
        }
        else {
            // MP가 ATK 미만: MP 회복, ATK 절반 피해
            c1.mp += 10;
            damage_c1_to_c2 = c1.attack / 2;
        }

        // --- C2의 행동 (C1에게 가하는 피해 계산) ---
        if (c2.mp >= c2.attack) {
            // MP가 ATK 이상: MP 소모, ATK만큼 피해
            c2.mp -= c2.attack;
            damage_c2_to_c1 = c2.attack;
        }
        else {
            // MP가 ATK 미만: MP 회복, ATK 절반 피해
            c2.mp += 10;
            damage_c2_to_c1 = c2.attack / 2;
        }

        // --- 방어력 적용 (동시 피해) ---
        // 자신이 받는 피해 = max(0, 상대방 공격포인트 - 자신의 방어력)
        int final_damage_c1_to_c2 = max_int(0, damage_c1_to_c2 - c2.defense);
        int final_damage_c2_to_c1 = max_int(0, damage_c2_to_c1 - c1.defense);

        // 첫 턴에 둘 다 피해가 0이면 즉시 무승부 처리 (문제 조건)
        if (turn == 0 && final_damage_c1_to_c2 == 0 && final_damage_c2_to_c1 == 0) {
            return 0; // 무승부
        }

        // --- HP 감소 ---
        c1.hp -= final_damage_c2_to_c1;
        c2.hp -= final_damage_c1_to_c2;

        // --- 승패 판정 ---
        int c1_died = (c1.hp <= 0);
        int c2_died = (c2.hp <= 0);

        if (c1_died && c2_died) {
            return 0; // 같은 턴에 둘 다 0 이하: 무승부
        }
        else if (c1_died) {
            return 2; // C2 승리
        }
        else if (c2_died) {
            return 1; // C1 승리
        }
    }

    // 최대 턴에 도달하면 안전하게 무승부 처리
    return 0;
}

int main()
{
    Character list[MAX_CHARACTERS];
    FILE* fp_in;
    FILE* fp_out;
    char inputName[64];
    int inputNumber;
    int count = 0; // 실제로 읽어온 캐릭터 수

    // --- 1. 사용자 입력 (학번/이름) ---
    printf("학번을 입력하세요: ");
    if (scanf_s("%d", &inputNumber) != 1) {
        fprintf(stderr, "학번 입력 오류\n");
        return 1;
    }
    clear_input_buffer();

    printf("이름을 입력하세요: ");
    // scanf_s는 버퍼 크기를 명시해야 함
    if (scanf_s("%63s", inputName, (unsigned)_countof(inputName)) != 1) {
        fprintf(stderr, "이름 입력 오류\n");
        return 1;
    }
    clear_input_buffer();

    // --- 2. 입력 파일 (students.csv) 열기 및 데이터 로드 ---
    if (fopen_s(&fp_in, "students.csv", "r") != 0 || fp_in == NULL) {
        printf("students.csv 파일을 열 수 없습니다.\n");
        // 파일 열기 실패 시 Test.txt에는 아무것도 출력할 수 없음. 에러 처리 후 종료.
        return 1;
    }

    char line[256];
    while (fgets(line, sizeof(line), fp_in) != NULL && count < MAX_CHARACTERS) {

        // 개행/캐리지 리턴 제거 (Windows/Linux 호환성을 위해)
        size_t len = strlen(line);
        while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r')) {
            line[len - 1] = '\0';
            len--;
        }

        if (len == 0) continue;

        // C4996 경고를 피하기 위해 strtok_s 사용
        char* context = NULL;
        char* token = strtok_s(line, ",", &context);

        // 이름
        if (!token) continue;
        strcpy_s(list[count].name, sizeof(list[count].name), token);

        // 공격력
        token = strtok_s(NULL, ",", &context);
        if (!token) continue;
        list[count].attack = atoi(token);

        // 방어력
        token = strtok_s(NULL, ",", &context);
        if (!token) continue;
        list[count].defense = atoi(token);

        // HP
        token = strtok_s(NULL, ",", &context);
        if (!token) continue;
        list[count].hp = atoi(token);

        // MP
        token = strtok_s(NULL, ",", &context);
        if (!token) {
            // MP가 없을 경우 기본값 설정 (0) 또는 오류 처리
            list[count].mp = 0;
        }
        else {
            list[count].mp = atoi(token);
        }

        count++;
    }

    fclose(fp_in);

    // --- 3. 출력 파일 (Test.txt) 열기 ---
    if (fopen_s(&fp_out, "Test.txt", "w") != 0 || fp_out == NULL) {
        printf("Test.txt 파일을 열 수 없습니다.\n");
        return 1;
    }

    // 데이터가 충분하지 않을 경우를 대비하여 최소 인원 체크 (11명, 인덱스 10까지 필요)
    if (count < 11) {
        // 시험 문제의 모든 항목을 처리하기에 데이터가 부족할 수 있음.
        // 출력 포맷 유지를 위해 부족한 경우에도 처리 가능한 부분만 출력
        fprintf(stderr, "경고: CSV 파일의 캐릭터 수가 11명 미만입니다 (현재 %d명).\n", count);
    }

    // =========================================================================
    // (1) 첫 번째 줄: 학번 : 이름 (10점)
    // =========================================================================
    fprintf(fp_out, "%d : %s\n", inputNumber, inputName);

    // =========================================================================
    // (2) 두 번째 줄: 7번째(list[6]) 8번째(list[7]) 이름 (10점)
    // =========================================================================
    if (count >= 8) {
        fprintf(fp_out, "%s %s\n", list[6].name, list[7].name);
    }
    else {
        fprintf(fp_out, "데이터 부족\n"); // 데이터가 부족할 경우 처리
    }

    // =========================================================================
    // (3) 세 번째 줄: Mother(list[6]) vs Horo(list[7]) 전투 결과 (20점)
    // =========================================================================
    if (count >= 8) {
        // Mother는 7번째 (list[6]), Horo는 8번째 (list[7])로 간주
        Character mother = list[6];
        Character horo = list[7];

        int result = simulate_fight(mother, horo);

        if (result == 1) { // Mother 승
            fprintf(fp_out, "%s 승! , %s 패\n", mother.name, horo.name);
        }
        else if (result == 2) { // Horo 승
            fprintf(fp_out, "%s 승! , %s 패\n", horo.name, mother.name);
        }
        else { // 무승부
            fprintf(fp_out, "무승부\n");
        }
    }
    else {
        fprintf(fp_out, "전투 시뮬레이션 데이터 부족\n");
    }

    // =========================================================================
    // (4) 네 번째 줄: Mother와 싸워서 이길 수 있는 사람 모두 출력 (20점)
    // =========================================================================
    if (count > 0) {
        Character mother_ref = list[6]; // Mother는 7번째 사람
        int first_winner = 1; // 쉼표 처리를 위한 플래그
        int winner_count = 0;

        // 승리자 이름들을 저장할 임시 문자열
        char winners[1024] = "";

        for (int i = 0; i < count; i++) {
            // 자기 자신 (Mother)과는 싸우지 않음
            if (i == 6) continue;

            // i번째 캐릭터 vs Mother (list[6])
            int result = simulate_fight(list[i], mother_ref);

            if (result == 1) { // i번째 캐릭터 승리
                winner_count++;

                if (!first_winner) {
                    strcat_s(winners, sizeof(winners), ", ");
                }
                strcat_s(winners, sizeof(winners), list[i].name);
                first_winner = 0;
            }
        }

        if (winner_count > 0) {
            fprintf(fp_out, "%s 승!\n", winners);
        }
        else {
            fprintf(fp_out, "%s 승!\n", mother_ref.name);
        }

    }
    else {
        fprintf(fp_out, "데이터 부족으로 Mother의 승리자를 판별할 수 없습니다.\n");
    }

    // =========================================================================
    // (5) 다섯 번째 줄: 9, 10, 11번째 사람의 이름을 연속해서 출력 (10점)
    // =========================================================================
    if (count >= 11) {
        fprintf(fp_out, "%s%s%s\n", list[8].name, list[9].name, list[10].name);
    }
    else if (count > 0) {
        // 데이터가 부족해도 가능한 부분까지 출력
        for (int i = 8; i < 11; i++) {
            if (i < count) {
                fprintf(fp_out, "%s", list[i].name);
            }
        }
        fprintf(fp_out, "\n");
    }
    else {
        fprintf(fp_out, "\n"); // 데이터 없음
    }

    // =========================================================================
    // (6) 여섯, 일곱 번째 줄: CSV 파일 전체 인원의 평균 공격력/방어력 (20점)
    // =========================================================================
    if (count > 0) {
        long long total_atk = 0;
        long long total_def = 0;

        for (int i = 0; i < count; i++) {
            total_atk += list[i].attack;
            total_def += list[i].defense;
        }

        // 평균은 정수 나눗셈으로 계산
        int AverageAtk = (int)(total_atk / count);
        int AverageDef = (int)(total_def / count);

        fprintf(fp_out, "Average atk: %d\n", AverageAtk);
        fprintf(fp_out, "Average def: %d\n", AverageDef);
    }
    else {
        fprintf(fp_out, "Average atk: 0\nAverage def: 0\n");
    }

    // =========================================================================
    // (7) 여덟 번째 줄 (마지막 줄): 고정 문장
    // =========================================================================
    fprintf(fp_out, "교수님 시험문제 너무 쉽습니다. 담주에 더 어렵게 내주세요.\n");

    // 파일 닫기 및 종료
    fclose(fp_out);

    printf("Test.txt 파일에 시험 결과가 성공적으로 작성되었습니다.\n");

    return 0;
}