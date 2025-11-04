#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    FILE* fp;
    errno_t err;
    char name[64], line[100];
    int number;

    // 파일 열기 (쓰기 모드: 새로 작성)
    err = fopen_s(&fp, "data.csv", "w");
    if (err != 0 || fp == NULL) {
        printf("파일 열기 실패!\n");
        return 1;
    }

    printf("몇명 입력하시겠습니까?\n");
    int people;
    
    scanf_s("%d", &people);

    // CSV 헤더 작성
    fprintf_s(fp, "학번,이름\n");

    while (people--)
    {
        // 사용자 입력 받기
        printf("학번과 이름을 작성하세요");

        printf("\n학번 : ");
        scanf_s("%d", &number);

        printf("이름 : ");
        scanf_s("%63s", name, 64);

        fprintf_s(fp, "%d,%s\n", number, name);
    }

    fclose(fp);

    err = fopen_s(&fp, "data.txt", "w");
    if (err != 0 || fp == NULL) {
        printf("파일 열기 실패!\n");
        return 1;
    }

    fprintf_s(fp, "%d : %s\n", number, name);
    printf("저장 완료!\n");

    fclose(fp);

    err = fopen_s(&fp, "data.csv", "r");
    if (err != 0 || fp == NULL) {
        printf("파일 열기 실패!\n");
        return 1;
    }

    /*if (fgets(line, sizeof(line), fp) != NULL) {
        printf("CSV 헤더: %s", line);
    }*/

    // 헤더 밑 모든 줄 읽기
    while (fgets(line, sizeof(line), fp) != NULL) {
        line[strcspn(line, "\n")] = 0;

        char* csv_number = strtok(line, ",");  // 학번
        char* csv_name = strtok(NULL, ",");    // 이름

        if (csv_number != NULL && csv_name != NULL) {
            int num = atoi(csv_number);
            line[strcspn(line, "\n")] = 0;
            printf("이름: %s, 번호: %d\n", csv_name, num);
        }
    }


    fclose(fp);    

}
