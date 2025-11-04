#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define LINE_CAP 256

int main(void)
{
	const char* filename = "testfile.txt";
	const char* line1 = "안녕하십니까. 이건 테스트 텍스트 파일 생성 코드입니다.";
	const char* line2 = "여긴 두 번째 줄입니다.";

	FILE* fp = NULL;
	fopen_s(&fp, filename, "w");

	//fopen_s에게 &fp라는 주소에 filename을 전달하라고 지시.
	//fopen_s는 배달 방식 "w"로 실제 주소 fp에 전달해줌. "w"는 쓰기 모드.
	
	if (fp == NULL) {
		perror("파일 열기 실패");
		return EXIT_FAILURE;
	}

	if (fprintf(fp, "%s\n", line1) < 0) {
		perror("파일 쓰기 실패(line1)");
		fclose(fp);
		return EXIT_FAILURE;
	}

	// fprintf(지정된 파일, 작성할 내용(a), a) <-- fprintf는 파일에 ()안의 내용을 작성함.
	// if (fprintf(fp, "%s\n", line1) < 0) <-- 작성에 성공하면 fprintf 값은 1 이상이 됨. 즉 실패할 경우 작성된 오류 관련 코드가 실행되는 것.
	
	if (fprintf(fp, "%s\n", line2) < 0) {
		perror("파일 쓰기 실패(line2)");
		fclose(fp);
		return EXIT_FAILURE;
	}

	if (fclose(fp) == EOF) {
		perror("파일 닫기 실패(쓰기 단계)");
		return EXIT_FAILURE;
	}
	return 0;
}