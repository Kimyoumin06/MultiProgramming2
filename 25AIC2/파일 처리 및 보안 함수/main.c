#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define MAX_CHARACTERS 100

typedef struct {
    char name[50];
    int attack;
    int defense;
    int hp;
} Character;

void clear_input_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// scanf_s 등 입력 받고 나면 항상 뒤에 찌꺼기로 \n이 남음.
// 이로 인해 뒤에 또 다시 입력 받는 코드는 이미 사용자가 입력을 마친 줄 알고 스킵하는 문제가 발생함.
// clear_input_buffer는 입력 후 찌꺼기로 남는 \n을 제거하는 역할을 함.

// clear_input_buffer 함수가 \n을 제거하는 방식은 getchar()를 사용하여
// 입력 받은 값을 하나하나 확인하면서 \n이나 EOF가 나올 때까지 계속 읽어들이고
// \n(혹은 파일 끝)까지 읽었기에 찌꺼기가 남지 않음.
// 그로 인해 다음 입력 함수가 정상적으로 작동하게 됨.

int main(void)
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

    // scanf_s "d"를 통해 숫자를 입력 받음.
	// 해당 값을 inpurtNumber를 담당하는 메모리에 저장함.
    // 이제 inputNumber를 호출하면 저장된 값이 출력됨.

    // 그런데 입력에 실패했을 경우 (scanf_s("%d", &inputNumber) != 1) 조건을 충족하게 됨.
    // 입력 성공 시, 1을 넘기게 됨.
	// 입력에 실패할 경우 if문이 실행되며
    // stderr를 통해 즉시 오류 메시지를 전달하며 "학번 입력 오류"를 출력하고 프로그램을 종료함.

    clear_input_buffer();

    printf("이름을 입력하세요: ");
    if (scanf_s("%63s", inputName, (unsigned)_countof(inputName)) != 1) {
        fprintf(stderr, "이름 입력 오류\n");
        return 1;
    }

	// scanf_s "%s"를 통해 문자열을 입력 받음.
	// 입력 받는 문자 크기는 63바이트(뒤에 \n 때문). 입력 받는 값의 이름을 inputName으로 지정.
	// 최대 크기는 (unsigned)_countof(inputName)로 지정 즉 64바이트.

	// 입력에 성공 시 1을 넘기고, 실패 시 0이 되어 if문이 실행됨.
    // stderr를 통해서 사용자에게 즉시 오류 임을 알리고 메시지를 출력함.
    // 이후 return 1; 통해 비정상 종료시킴.

    // (unsigned)_countof(inputName)의 정의.
	// _countof()는 ()안에 있는 자료를 크기로 변환해주는 코드임.
	// inpuName이 64로 선언 되었기에 64로 변환됨. = (unsigned)64
    // (unsigned)는 일반 숫자로 변환해주는 코드, 즉 int형으로 변환시켜줌.

    clear_input_buffer();

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