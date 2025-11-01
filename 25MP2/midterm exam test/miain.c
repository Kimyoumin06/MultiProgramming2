#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define LINE_CAP 256

int main(void)
{
	const char* filename = "testfile.txt";
	const char* line1 = "�ȳ��Ͻʴϱ�. �̰� �׽�Ʈ �ؽ�Ʈ ���� ���� �ڵ��Դϴ�.";
	const char* line2 = "���� �� ��° ���Դϴ�.";

	FILE* fp = NULL;
	fopen_s(&fp, filename, "w");

	//fopen_s���� &fp��� �ּҿ� filename�� �����϶�� ����.
	//fopen_s�� ��� ��� "w"�� ���� �ּ� fp�� ��������. "w"�� ���� ���.
	
	if (fp == NULL) {
		perror("���� ���� ����");
		return EXIT_FAILURE;
	}

	if (fprintf(fp, "%s\n", line1) < 0) {
		perror("���� ���� ����(line1)");
		fclose(fp);
		return EXIT_FAILURE;
	}

	// fprintf(������ ����, �ۼ��� ����(a), a) <-- fprintf�� ���Ͽ� ()���� ������ �ۼ���.
	// if (fprintf(fp, "%s\n", line1) < 0) <-- �ۼ��� �����ϸ� fprintf ���� 1 �̻��� ��. �� ������ ��� �ۼ��� ���� ���� �ڵ尡 ����Ǵ� ��.
	
	if (fprintf(fp, "%s\n", line2) < 0) {
		perror("���� ���� ����(line2)");
		fclose(fp);
		return EXIT_FAILURE;
	}

	if (fclose(fp) == EOF) {
		perror("���� �ݱ� ����(���� �ܰ�)");
		return EXIT_FAILURE;
	}
	return 0;
}