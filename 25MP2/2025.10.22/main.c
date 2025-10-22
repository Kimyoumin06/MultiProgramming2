#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <string.h>

#define LINE_CAP 256
#define MAX_LOG_LINES 1000

struct Fish {
    char *name;
    char *talk;

    int answer;

    char *talk_O;
    char *talk_X;
};

typedef struct {
    char name[50];
    char result; // 'O' or 'X'
} QuizResult;

int main(void)
{
    struct Fish fishes[5] = {
        {"스폰지", "전 스폰지밥 창작자는 어떤 학과였을까?\n1.멀티미디어공학과 2.해양생물학과 3.치위생과 4.애니메이션학과", 2,"맞습니다.\n 스펀지밥 창작자 스티븐 힐렌버그는 해양생물학을 전공하였고 해당 교사였습니다.","안타까워라 다시 시도하세요"},
        {"불가사리", "선박에 들러붙어 처치 곤란이었던 불가사리의 쓰임새가 생겼다. 어디에 쓰일까?\n1.여러 식품 2.장식품 3.화장품 4.부메랑 같은 장난감", 3,"맞습니다.\n불가사리는 최근 피부 미용 관련 화장품에 사용되고 있습니다.","뉴스 좀 보세요, 어떻게 뚱이보다 모르는 게 많지?"},
        {"문어", "문어의 지능은 어느정도 일까?\n1.사람의 3~5세 정도 2.사람의 2세 정도 3.초등학생 정도 4.교수님 정도", 1,"맞습니다. 문어는 사람의 약 3~5세 정도의 지능을 가지고 있습니다.","문어보다 조금 부족한 면이 있으시네요"},
        {"게", "가재의 수명은 얼마나 될까?\n1.30년 이상 2.약 5~10년 3.약 15년 4.무한 이상", 4,"실제로 가재의 수명은 이론상 무한입니다. 하지만 탈피하는 과정에서 죽는 경우가 허다합니다.","게가 왜 가재 문제내냐고? 게는 원래 가재편이야. 공부나 해."},
        {"다람쥐", "산에 가면 도토리 나무가 많이 자라 있는데 이유가 뭘까?\n1.다람쥐 같은 생물 보호를 위해 사람이 심어서 2.다람쥐가 농사하기 위해 심어서 3.위대한 다람쥐가 누군가한테 시켜서 4.숨겨놓고 까먹어서", 4,"맞습니다. 다람쥐는 식량 저장을 위해 도토리를 숨기지만 그중 70%는 위치를 까먹습니다.","너보단 도토리 위치 까먹은 내가 낫다"},
    };

    const char* filename = "log.txt";
    FILE* fp;
    int totalGames = 0;      // 게임 횟수
    int totalCorrect = 0;    // 누적 맞은 문제 수
    int totalQuestions = 0;  // 누적 푼 문제 수

    // --- 1. log.txt 읽기 ---
    fp = fopen(filename, "r");
    if (fp == NULL) {
        totalGames = 0;
        totalCorrect = 0;
        totalQuestions = 0;
    }
    else {
        char line[LINE_CAP];
        // 1줄: 누적 게임 횟수
        if (fgets(line, sizeof(line), fp) != NULL) {
            sscanf(line, "%d", &totalGames);
        }

        // 2줄: 누적 맞춘 문제, 총 문제
        if (fgets(line, sizeof(line), fp) != NULL) {
            sscanf(line, "%d %d", &totalCorrect, &totalQuestions);
        }

        fclose(fp);
    }

    totalGames++;  // 이번 게임 횟수 증가

    // --- 2. 게임 시작 메시지 ---
    printf("%d번째 게임입니다!!\n", totalGames);
    if (totalQuestions > 0) {
        printf("정답률: %d/%d\n\n", totalCorrect, totalQuestions);
    }
    else {
        printf("아직 정답 기록이 없습니다.\n\n");
    }

    // --- 3. 게임 진행 변수 ---
    int fishing = 1;
    int Answer;
    int correctThisGame = 0;
    int questionsThisGame = 0;

    QuizResult results[100];
    int resultCount = 0;

    srand((unsigned int)time(NULL));

    // --- 4. 게임 루프 ---
    while (fishing)
    {
        printf("찌를 던진다 (Y/N) >");
        char yn = _getch();
        printf("%c\n", yn);

        if (yn == 'y' || yn == 'Y')
        {
            system("cls");
            printf("당신은 찌를 던졌다!\n");
            int waiting = 5;
            while (waiting)
            {
                Sleep(500);
                printf(".");
                waiting--;
            }
            printf("\n\033[32m입질이 왔다!!\033[0m\n");

            int idx = rand() % 5;

            printf("오늘의 물고기 퀴즈!\n");
            printf("%s : %s\n", fishes[idx].name, fishes[idx].talk);

            Answer = _getch();
            printf("%c\n", Answer);

            questionsThisGame++;

            if (Answer - '0' == fishes[idx].answer)
            {
                printf("%s\n", fishes[idx].talk_O);
                correctThisGame++;

                results[resultCount].result = 'O';
            }
            else
            {
                printf("%s\n", fishes[idx].talk_X);
                Sleep(200);
                printf("\n%s는 낚시찌에서 빠져나와 멀리 사라졌다..", fishes[idx].name);
                results[resultCount].result = 'X';
            }

            strcpy(results[resultCount].name, fishes[idx].name);
            resultCount++;

            Sleep(5000);
            system("cls");
        }
        else if (yn == 'n' || yn == 'N')
        {
            printf("당신은 낚시를 관두었다..\n");
            fishing = 0;
        }
        else
        {
            printf("실수로 미끼를 놓쳤다.. 다시 시도하자..\n");
        }
    }

    // --- 5. 기록 업데이트 ---
    totalCorrect += correctThisGame;
    totalQuestions += questionsThisGame;

    // --- 6. 기존 로그 읽기 및 보존 ---
    char* logs[MAX_LOG_LINES];
    int logCount = 0;

    fp = fopen(filename, "r");
    if (fp != NULL) {
        char temp[LINE_CAP];
        // 첫 2줄은 이미 읽었으니 넘김
        fgets(temp, sizeof(temp), fp);
        fgets(temp, sizeof(temp), fp);

        while (fgets(temp, sizeof(temp), fp) != NULL && logCount < MAX_LOG_LINES) {
            logs[logCount] = (char*)malloc(strlen(temp) + 1);
            strcpy(logs[logCount], temp);
            logCount++;
        }
        fclose(fp);
    }

    // --- 7. 로그 파일 쓰기 ---
    fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("로그 파일 열기 실패");
        return EXIT_FAILURE;
    }

    fprintf(fp, "%d\n", totalGames);
    fprintf(fp, "%d %d\n", totalCorrect, totalQuestions);

    // 기존 기록 유지
    for (int i = 0; i < logCount; i++) {
        fputs(logs[i], fp);
        free(logs[i]);
    }

    // 이번 게임 기록 추가
    for (int i = 0; i < resultCount; i++) {
        fprintf(fp, "%s\n%c\n", results[i].name, results[i].result);
    }

    fclose(fp);

    // --- 8. 최종 정답률 출력 ---
    printf("게임 종료! 누적 정답률: %d/%d\n", totalCorrect, totalQuestions);

    return 0;
}
