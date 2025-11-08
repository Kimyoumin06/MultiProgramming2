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
	// inpuName이 64로 선언 되었기에 64로 변환됨. = (unsigned)64 = int 형 64.
    // (unsigned)는 일반 숫자로 변환해주는 코드, 즉 int형으로 변환시켜줌.

    clear_input_buffer();

    if (fopen_s(&fp, "students.csv", "r") != 0 || fp == NULL) {
        printf("students.csv 파일을 열 수 없습니다.\n");
        return 1;
    }

	// fopen_s를 통해 students.csv 파일을 읽기 모드("r")로 엶.
    // r모드는 읽을 수만 있고, 파일을 수정할 순 없음.
	// 읽는데 성공하면 0(오류 없음)이 되고 if문이 실행되지 않음.
	// fp에는 students.csv 파일의 주소가 저장됨. 이후 fp를 통해 파일에 접근 가능.

    char line[256];

    if (fgets(line, sizeof(line), fp) == NULL) {
        printf("students.csv 파일이 비어있거나 헤더를 읽을 수 없습니다.\n");
        fclose(fp);
        return 1;
    }

	// sizeof()은 ()안에 있는 자료의 크기를 최대로 지정해줌. 즉 line의 256이 최대 값임.
	// fp는 students.csv 파일의 주소가 저장 되어 있음. 즉 해당 파일을 읽고 있다는 뜻임.
	// fgets로 파일 한 줄을 읽는데 실패하면 NULL이 되어 if문이 실행됨.

    // fgets = 파일 한 줄 읽기 및 저장 함수.
    // line = fgets를 통해 읽은 내용을 저장할 변수.
	// sizeof() = 최대 크기 지정 함수. line이 들어감으로 line의 크기인 256이 최대 크기가 됨.
	// fp = (students.csv) 파일의 주소. fgets가 방문할 주소를 알려주는 역할을 함.

    while (fgets(line, sizeof(line), fp) != NULL && count < MAX_CHARACTERS) {

		// 해당 while문은 파일을 성공적으로 읽고, 저장된 최대 캐릭터 값이 100 미만일 때 반복됨.
		// && count < MAX_CHARACTERS. 여기서 MAX_CHARACTERS는 100으로 정의 되어 있음.
        // == count < 100
		
        // fgets는 실행 될 때마다 한 줄씩 읽어감.
        // 첫 번째 실행 때 첫 번째 줄, 두 번째 실행 때 두 번째 줄... 반복 됨.
        // 이전에 fgets가 한 번 실행 되었기에, 헤더 부분(첫 번째 줄)이 넘어가진 상태.
        // 현 while문에서는 두 번째 줄부터 읽음.

        size_t len = strlen(line);
        // strlen() = ()안 문자의 길이를 구분하는 함수.
        // fgets로 읽어서 line 안에 저장된 값은 전부 문자열임.
		// len은 line에 저장된 문자열의 길이를 저장함(\0 제외).

        while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r')) {
            line[len - 1] = '\0';
            len--;
        }
        // line[len - 1]는 저장된 문자의 가장 마지막 문자를 의미함.
		// len(line에 저장된 문자 갯수 > 0) && line의 가장 마지막 문자가 엔터(\n)거나 개행 문자(\r)라면
        // 안에 있는 코드를 반복 실행함.
        // line에는 fgets를 통해 파일 내 값이 저장된 것임으로 파일에서 해당 줄에 저장된 문자가 있어야함.
        
		// 내부의 코드는 line의 마지막 문자를 \0 공백으로 변경시킴.
        // 그리고 지워져도 괜찮기 때문에 길이를 줄임으로써 해당 문자를 지움.

        if (len == 0) continue;
		// len은 line에 저장된 문자열의 길이임.
		// 즉 len이 0이라는 뜻은 line에 저장된 문자가 없다는 뜻.
        // == 파일에서 해당 줄은 빈 줄이라는 걸 의미함.
        // continue는 실행중인 루프를 즉시 중단 시키고 재실행 시키는 역할을 하는 코드임.

        // 즉 파일에 빈 줄이 있으면 재실행 하라는 뜻.
        // 재실행 하면 fgets가 다시 작동하여 줄을 넘기기 때문에 괜찮음.

        char* context = NULL;
        // context는 NULL을 통해서 항상(while로 반복되기 때문) 값을 초기화 함.

        char* token = strtok_s(line, ",", &context);
		// strtok_s = 문자열을 특정 구분자로 나누는 함수.
        // line은 읽은 파일(CSV)의 한 줄이 저장되어 있음.
        // CSV는 , <-- 로 이미 구분 되어 있음.
		// ,를 기준으로 나눴다는 상태를 &context에 저장함.
		// line에 "유민,50,30,200" 이런 식으로 저장되어 있다면
		// &context에 기존 문자로 저장되어 있던 ,가 구분점으로 작용할 수 있도록 약간 수정하는 느낌.

        // token에는 line에 있던 문자들과 &context로 구분되어 있는 상태를 동시에 저장하고 있음.

        if (!token) continue;
        // token을 성공적으로 얻지(구분하지) 못했다면 반려시킴.
		// 못했다의 기준은 빈 줄이거나 잘못된 형식의 줄일 경우.
        
        strcpy_s(list[count].name, sizeof(list[count].name), token);
		// strcpy_s = 문자열 복사 함수.
		// list[count].name <-- 저장할 위치.
		// sizeof(list[count].name) <-- 최대 크기.
		// token <-- 복사할 문자열.
		// token의 문자를 list[count].name에 옮김으로써 이름이 저장되고, 기존 line에 저장된 이름은 사라짐.
        // 이제 token에 유민\050,30,200임. 앞에 유민은 동시에 NULL 상태이기도 한 거임.
        // 여기서 \0은 문자열의 끝을 의미하기 때문에 이후 인식할 때 문제가 없음.

        token = strtok_s(NULL, ",", &context);
		// &context에 있던 유민,50,30,200에서 유민\0,50,30,200이 됨.
        // token은 \0(NULL)과 , 앞에 있는 50을 가장 처음으로 인식해서 token은 50으로 저장됨.
        // NULL을 기준으로 앞에 있는 건 무시됨.
		// 즉 유민\0(NULL) 50 , 이런 식으로 되어 있기 때문에 50이 가장 처음으로 인식되는 것임.
        
        if (!token) continue;
        
        list[count].attack = atoi(token);

		// atoi = 문자열을 정수로 변환하는 함수.
		// 현재 CSV 파일 상, 공격력 수치인 50이 token에 문자열로 저장되어 있음.
		// atoi(token)을 통해 50을 정수 50으로 변환시켜서 list[count].attack에 저장함.

        // 여기서 count는 0임.
		// 그리고 struct Character에서 [0] 즉 첫 번째에 저장함.

        token = strtok_s(NULL, ",", &context);
        // 앞에서 이해한 것과 같이 50\0로 처리됨.
		// 따라서 token에는 30이 저장됨.
        // 30을 token에 저장을 마쳤음으로 30 또한 NULL 처리함.
		// &context에는 유민\050\030\0200이 저장되어 있음.
        
        if (!token) continue;
        
        list[count].defense = atoi(token);
		// 첫 번째 Character의 방어력에 30이 정수로 저장됨.

        token = strtok_s(NULL, ",", &context);
		// token에는 200이 저장됨.
		// 200 또한 NULL 처리됨. == 유민\050\030\0200\0 상태가 됨.
        
        if (!token) continue;
        
        list[count].hp = atoi(token);
		// 첫 번째 Character의 hp에 200이 정수로 저장됨.

        count++;
        // count 값을 계속 증가시키면서, CSV 파일 내 캐릭터 전부를 저장함.
        // list[count]가 되어 있기 때문에, 공격력 같은 기타 정보들도 struct에 저장 시킴.
    }
    fclose(fp);
	// fclose = 파일 닫기 함수.
    // 파일을 열고 나면 항상 닫아줘야함.

    if (fopen_s(&fp, "Test.txt", "w") != 0 || fp == NULL) {
        printf("Test.txt 파일을 열 수 없습니다.\n");
        return 1;
    }
	// fopen_s를 통해 Test.txt 파일을 쓰기 모드("w")로 엶.
	// w모드는 파일이 없으면 새로 만들고, 있으면 기존 내용을 지우고 새로 작성하는 모드임.

    fprintf(fp, "%d : %s\n", inputNumber, inputName);
	// fprintf = 파일에 출력하는 함수.
	// 먼저 입력 받았던 학번과 이름을 파일에 기록함.

    if (count == 0) {
        printf("학생 데이터가 없습니다.\n");
        fprintf(fp, "학생 데이터가 없습니다.\n");
        fclose(fp);
        return 1;
    }
    // 만일 count가 0일 경우, 오류가 발생했음을 알리는 코드를 실행함.
	// count == 0이 학생이 없다는 뜻인 이유는 학생을 읽으면 count가 1씩 증가함.
    // 그런데 count가 늘어나지 않았다는 건 학생이 없다는 것과 같은 이치이기 때문.

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