#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

void demo_serch(void)
{
    puts("\n[데모4] 검색: strchr/strrchr/strstr");

    char text[100];
    fgets(text, sizeof(text), stdin);

    char buf[128];
    strcpy(buf, text);
    for (char* q = strstr(buf, "gay"); q != NULL; q = strstr(q + 1, "gay")) {
        strncpy(q, "***", 3);
    }
    printf("replace 'gay'->'***': \"%s\"\n", buf);
}

int main()
{
    demo_serch();
	return 0;
}