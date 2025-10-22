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
        {"������", "�� �������� â���ڴ� � �а�������?\n1.��Ƽ�̵����а� 2.�ؾ�����а� 3.ġ������ 4.�ִϸ��̼��а�", 2,"�½��ϴ�.\n �������� â���� ��Ƽ�� �������״� �ؾ�������� �����Ͽ��� �ش� ���翴���ϴ�.","��Ÿ����� �ٽ� �õ��ϼ���"},
        {"�Ұ��縮", "���ڿ� �鷯�پ� óġ ����̾��� �Ұ��縮�� ���ӻ��� �����. ��� ���ϱ�?\n1.���� ��ǰ 2.���ǰ 3.ȭ��ǰ 4.�θ޶� ���� �峭��", 3,"�½��ϴ�.\n�Ұ��縮�� �ֱ� �Ǻ� �̿� ���� ȭ��ǰ�� ���ǰ� �ֽ��ϴ�.","���� �� ������, ��� ���̺��� �𸣴� �� ����?"},
        {"����", "������ ������ ������� �ϱ�?\n1.����� 3~5�� ���� 2.����� 2�� ���� 3.�ʵ��л� ���� 4.������ ����", 1,"�½��ϴ�. ����� ����� �� 3~5�� ������ ������ ������ �ֽ��ϴ�.","����� ���� ������ ���� �����ó׿�"},
        {"��", "������ ������ �󸶳� �ɱ�?\n1.30�� �̻� 2.�� 5~10�� 3.�� 15�� 4.���� �̻�", 4,"������ ������ ������ �̷л� �����Դϴ�. ������ Ż���ϴ� �������� �״� ��찡 ����մϴ�.","�԰� �� ���� �������İ�? �Դ� ���� �������̾�. ���γ� ��."},
        {"�ٶ���", "�꿡 ���� ���丮 ������ ���� �ڶ� �ִµ� ������ ����?\n1.�ٶ��� ���� ���� ��ȣ�� ���� ����� �ɾ 2.�ٶ��㰡 ����ϱ� ���� �ɾ 3.������ �ٶ��㰡 ���������� ���Ѽ� 4.���ܳ��� ��Ծ", 4,"�½��ϴ�. �ٶ���� �ķ� ������ ���� ���丮�� �������� ���� 70%�� ��ġ�� ��Խ��ϴ�.","�ʺ��� ���丮 ��ġ ����� ���� ����"},
    };

    const char* filename = "log.txt";
    FILE* fp;
    int totalGames = 0;      // ���� Ƚ��
    int totalCorrect = 0;    // ���� ���� ���� ��
    int totalQuestions = 0;  // ���� Ǭ ���� ��

    // --- 1. log.txt �б� ---
    fp = fopen(filename, "r");
    if (fp == NULL) {
        totalGames = 0;
        totalCorrect = 0;
        totalQuestions = 0;
    }
    else {
        char line[LINE_CAP];
        // 1��: ���� ���� Ƚ��
        if (fgets(line, sizeof(line), fp) != NULL) {
            sscanf(line, "%d", &totalGames);
        }

        // 2��: ���� ���� ����, �� ����
        if (fgets(line, sizeof(line), fp) != NULL) {
            sscanf(line, "%d %d", &totalCorrect, &totalQuestions);
        }

        fclose(fp);
    }

    totalGames++;  // �̹� ���� Ƚ�� ����

    // --- 2. ���� ���� �޽��� ---
    printf("%d��° �����Դϴ�!!\n", totalGames);
    if (totalQuestions > 0) {
        printf("�����: %d/%d\n\n", totalCorrect, totalQuestions);
    }
    else {
        printf("���� ���� ����� �����ϴ�.\n\n");
    }

    // --- 3. ���� ���� ���� ---
    int fishing = 1;
    int Answer;
    int correctThisGame = 0;
    int questionsThisGame = 0;

    QuizResult results[100];
    int resultCount = 0;

    srand((unsigned int)time(NULL));

    // --- 4. ���� ���� ---
    while (fishing)
    {
        printf("� ������ (Y/N) >");
        char yn = _getch();
        printf("%c\n", yn);

        if (yn == 'y' || yn == 'Y')
        {
            system("cls");
            printf("����� � ������!\n");
            int waiting = 5;
            while (waiting)
            {
                Sleep(500);
                printf(".");
                waiting--;
            }
            printf("\n\033[32m������ �Դ�!!\033[0m\n");

            int idx = rand() % 5;

            printf("������ ����� ����!\n");
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
                printf("\n%s�� ������� �������� �ָ� �������..", fishes[idx].name);
                results[resultCount].result = 'X';
            }

            strcpy(results[resultCount].name, fishes[idx].name);
            resultCount++;

            Sleep(5000);
            system("cls");
        }
        else if (yn == 'n' || yn == 'N')
        {
            printf("����� ���ø� ���ξ���..\n");
            fishing = 0;
        }
        else
        {
            printf("�Ǽ��� �̳��� ���ƴ�.. �ٽ� �õ�����..\n");
        }
    }

    // --- 5. ��� ������Ʈ ---
    totalCorrect += correctThisGame;
    totalQuestions += questionsThisGame;

    // --- 6. ���� �α� �б� �� ���� ---
    char* logs[MAX_LOG_LINES];
    int logCount = 0;

    fp = fopen(filename, "r");
    if (fp != NULL) {
        char temp[LINE_CAP];
        // ù 2���� �̹� �о����� �ѱ�
        fgets(temp, sizeof(temp), fp);
        fgets(temp, sizeof(temp), fp);

        while (fgets(temp, sizeof(temp), fp) != NULL && logCount < MAX_LOG_LINES) {
            logs[logCount] = (char*)malloc(strlen(temp) + 1);
            strcpy(logs[logCount], temp);
            logCount++;
        }
        fclose(fp);
    }

    // --- 7. �α� ���� ���� ---
    fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("�α� ���� ���� ����");
        return EXIT_FAILURE;
    }

    fprintf(fp, "%d\n", totalGames);
    fprintf(fp, "%d %d\n", totalCorrect, totalQuestions);

    // ���� ��� ����
    for (int i = 0; i < logCount; i++) {
        fputs(logs[i], fp);
        free(logs[i]);
    }

    // �̹� ���� ��� �߰�
    for (int i = 0; i < resultCount; i++) {
        fprintf(fp, "%s\n%c\n", results[i].name, results[i].result);
    }

    fclose(fp);

    // --- 8. ���� ����� ��� ---
    printf("���� ����! ���� �����: %d/%d\n", totalCorrect, totalQuestions);

    return 0;
}
