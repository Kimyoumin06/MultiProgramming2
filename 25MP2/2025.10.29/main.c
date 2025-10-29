#define _CRT_SECURE_NO_WARNINGS

/*
    ���ϸ�: string_lab.c
    ����  : C�� <string.h>�� �������� ������ ���� "�ּ� ����" ����.
            ������, �̰� �� ���Ϸ� ����/�ǽ�/���� ���� Ŀ�� ����.

    ������:
      - MSVC(Windows): cl /W4 /Za string_lab.c
      - GCC/Clang    : gcc -Wall -Wextra -std=c11 string_lab.c -o string_lab

    �� ���Ͽ��� �ٷ�� �ٽ� �Լ���(<string.h>):
      ����/����/���̱�: strlen, strcpy, strncpy, strcat, strncat
      ��           : strcmp, strncmp
      �˻�           : strchr, strrchr, strstr
      ��ūȭ         : strtok, (MSVC���) strtok_s
      �޸� ���    : memcpy, memmove, memcmp, memset (���ʽ�)

    ?? �������� ������(���� �� �ݺ��ؼ� �ھ� ��������):
      1) "���ڿ�"�� �������� '\0'�� �ִ� char �迭�̴�. '\0' ������ �� �� �� ����.
      2) ���� ũ�� �𸣸� strcpy/strcat ���� "������" �Լ��� ����. ����δ� �����ֵ�, ���� �ڵ�� *_s �Ǵ� ���� ���� ���� ��� ����.
      3) fgets�� �Է� ������ ���� '\n'�� �ٴ´� �� ���� ���� �ʿ�.
      4) strtok�� �ı���(���� ���ڿ��� �����). ���� �����Ϸ��� ���纻���� ��ūȭ.
      5) memcpy vs memmove: ��ġ�� ����(overlap)�� ���� memmove�� ����.

    ��������������������������������������������������������������������������������������������������������������������������������������������������
*/

#include <stdio.h>
#include <string.h>   // ������ ���ΰ�
#include <stdlib.h>

//---------------------------------------------
// ��ƿ 1: ���ڿ� ���� ����('\n') ���ű�
//---------------------------------------------
void trim_newline(char* s)
{
    if (!s) return;
    size_t len = strlen(s);
    if (len && s[len - 1] == '\n') s[len - 1] = '\0';
}

//---------------------------------------------
// ��ƿ 2: ���� �Է� (fgets + ���� ����)
//   - scanf("%s")�� ���鿡�� �����, ���� �����÷ο� ����.
//   - fgets�� ���� ������ �е�, ���� '\n'�� ���� �� trim �ʿ�.
//---------------------------------------------
void input_line(const char* prompt, char* buf, size_t bufsize)
{
    if (prompt) fputs(prompt, stdout);
    if (fgets(buf, (int)bufsize, stdin) == NULL) {
        // �Է� ���� ��, �� ���ڿ���
        if (bufsize) buf[0] = '\0';
        return;
    }
    trim_newline(buf);
}

//---------------------------------------------
// ���� 1: ���� �Լ� (strlen)
//   - sizeof�� strlen ���� �ݵ�� ü����Ű��
//---------------------------------------------
void demo_strlen(void)
{
    puts("\n[����1] strlen vs sizeof");
    char s1[10] = "abc";         // 'a','b','c','\0', ������ ������
    char s2[] = "hello";       // �����Ϸ��� ũ�� 6���� ����(������ '\0' ����)

    printf("s1=\"%s\"  sizeof(s1)=%zu, strlen(s1)=%zu\n",
        s1, sizeof(s1), strlen(s1));
    printf("s2=\"%s\"  sizeof(s2)=%zu, strlen(s2)=%zu\n",
        s2, sizeof(s2), strlen(s2));

    // �Ǽ� ����: �ι��� ����� strlen�� ���� ���ڴ�(�����ֱ⸸ �ϰ� �ٽ� ����)
    char demo[] = "XYZ";
    printf("before: \"%s\" (strlen=%zu)\n", demo, strlen(demo));
    demo[3] = 'Q'; // '\0'�� �������� �� ���� ���� ����(UB ����)
    // printf("after : \"%s\"\n", demo); // ���� ����. ������� �ʴ� �� ����.
    demo[3] = '\0'; // ����
}

//---------------------------------------------
// ���� 2: ����/���̱� (strcpy/strncpy, strcat/strncat)
//   - *_n ������ 'n'�� "�ҽ����� ���� �ִ� ����"��, ������ ũ�⸦ �������� �ʴ´�.
//   - ���� ������ �� �뷮�� �˰� �־�� �����÷ο츦 ���� �� �ִ�.
//   - MSVC/Annex K ��� �����ϸ� strcpy_s/strcat_s�� ���.
//---------------------------------------------
void demo_copy_concat(void)
{
    puts("\n[����2] ����/���̱�: strcpy/strncpy, strcat/strncat");

    char dest[16];       // �� �뷮 16
    char a[] = "hello";
    char b[] = " world!";

    // 1) strcpy: '\0' �����ؼ� ����. dest ����� Ŀ�� ��.
    strcpy(dest, a);     // dest := "hello"
    printf("after strcpy: '%s'\n", dest);

    // 2) strcat: dest ���� ����. dest ���� ���� + ���� ���� + 1('\0') <= �뷮
    strcat(dest, b);     // dest := "hello world!"
    printf("after strcat: '%s'\n", dest);

    // 3) strncpy: �ҽ����� �ִ� n���� "�о�" �����ϵ�, '\0' ���� X
    //    �� ���� '\0' �����ϰų�, ������ 0 ä��� �ʿ�.
    char dest2[8];
    // 'hello'�� 7���ڱ��� �о� ����. 'hello'�� 5���ڶ� '\0'���� ��.
    strncpy(dest2, a, sizeof(dest2) - 5);
    dest2[sizeof(dest2) - 1] = '\0'; // �׻� �������� '\0' ����
    printf("after strncpy (safe): '%s'\n", dest2);

    // 4) strncat: �ִ� n���ڸ� "����". n�� ���� �ҽ� �ִ� ����.
    char dest3[10] = "he";
    strncat(dest3, "lloXX", 3); // 'llo'�� ���� �� "hello"
    printf("after strncat: '%s'\n", dest3);

    // ? Annex K / MSVC ����(������ ȯ�濡�� ��õ)
    //    ������ ũ�⸦ ���ڷ� �޾Ƽ� �����÷ο� ������ ����.
    // #ifdef _MSC_VER
    //     char safe[16] = {0};
    //     strcpy_s(safe, sizeof(safe), "ABC");
    //     strcat_s(safe, sizeof(safe), "DEF");
    //     printf("MSVC safe funcs: '%s'\n", safe);
    // #endif
}

//---------------------------------------------
// ���� 3: �� (strcmp/strncmp)
//   - ������ ��: a<b�� ����, ������ 0, a>b�� ���
//---------------------------------------------
void demo_compare(void)
{
    puts("\n[����3] ��: strcmp/strncmp");

    const char* x = "apple";
    const char* y = "apricot";
    const char* z = "apple";

    printf("strcmp('%s','%s') = %d\n", x, y, strcmp(x, y)); // 'l' vs 'r' �� ����
    printf("strcmp('%s','%s') = %d\n", x, z, strcmp(x, z)); // ���� �� 0

    // ���ξ� ��: ���� 3���ڸ�
    printf("strncmp('%s','%s',3) = %d\n", x, y, strncmp(x, y, 3)); // 'apr' vs 'app' �� ���/���� Ȯ��
}

//---------------------------------------------
// ���� 4: �˻� (strchr/strrchr/strstr)
//   - strchr   : ���� ù ��ġ
//   - strrchr  : ���� ������ ��ġ
//   - strstr   : �κ� ���ڿ� ù ��ġ
//---------------------------------------------
void demo_search(void)
{
    puts("\n[����4] �˻�: strchr/strrchr/strstr");

    const char* text = "the quick brown fox jumps over the lazy dog";

    const char* p1 = strchr(text, 'o');   // ù 'o'
    const char* p2 = strrchr(text, 'o');  // ������ 'o'
    const char* p3 = strstr(text, "own"); // "own" ���� ��ġ

    printf("text          : \"%s\"\n", text);
    printf("strchr 'o'    : %s\n", p1 ? p1 : "(NULL)");
    printf("strrchr 'o'   : %s\n", p2 ? p2 : "(NULL)");
    printf("strstr \"own\" : %s\n", p3 ? p3 : "(NULL)");

    // ������ ���̶���Ʈ: 'o'�� '*'�� ��� �ٲٱ�(�ı���)
    char buf[128];
    strcpy(buf, text);
    for (char* q = strchr(buf, 'o'); q != NULL; q = strchr(q + 1, 'o')) {
        *q = '*';
    }
    printf("replace 'o'->'*': \"%s\"\n", buf);
}

//---------------------------------------------
// ���� 5: ��ūȭ (strtok / strtok_s)
//   - ����/��ǥ/�����ݷ� �� �����ڷ� ���ڿ��� �߶� "��ū" ������
//   - strtok�� ������ �ı��Ѵ�. ���� �����Ϸ��� ���纻���� �۾�.
//   - ���� ������/���� �Ľ̿��� ������ �� (MSVC) strtok_s ��� ���� ����.
//---------------------------------------------
void demo_tokenize(void)
{
    puts("\n[����5] ��ūȭ: strtok / strtok_s");

    char src[] = "Alice,Bob;Charlie David"; // ���� �ı��� ����(������)
    char copy[64];
    strcpy(copy, src);

    // 1) strtok (ǥ��) ? ������ ���� X, ���� static ����
    //    ù ȣ��: strtok(���ڿ�, �����ڵ�)
    //    �̾� ȣ��: strtok(NULL, ������ �����ڵ�)
    {
        char temp[64];
        strcpy(temp, copy);

        const char* delims = " ,;";    // ������(Delimiter) ����. ���⼭�� '�����̽�', '�޸�', '�����ݷ�' �� �ϳ��� ������ �ڸ���.
        // ��: "A, B;C D" �� "A" | "B" | "C" | "D"

        char* tok = strtok(temp, delims); // ù ȣ��: ��ūȭ ����.
        // - temp ���ڿ��� ���ʺ��� �ȴٰ� delims �� �ϳ��� ������ �� ��ġ�� '\0'�� �־� ���ڿ��� '���´�'.
        // - ��ȯ���� ��� 'ù ��° ��ū'�� ���� �ּ�.
        // - ���������� static ���� �����͸� ��� �� ���� ȣ����� �̾ ���� ����.
        //   (�� ������ ��Ƽ������/��ø ��뿡 ���. ���: strtok_s)

        int idx = 0;                    // ��ū ��ȣ(�ε���) ī����

        printf("[strtok] tokens:");     // ��� �����Ƚ�. �̾ �� ��ū�� [��ȣ:���ڿ�] ���·� �ٿ��� ����Ѵ�.

        while (tok) {                   // ��ū�� NULL�� �ƴ� ���� �ݺ� (��, �� �̻� �ڸ� ��ū�� ���� ������)
            printf(" [%d:%s]", idx++, tok); // ���� ��ū ���: ���� �ϳ� + [�ε���:��ū] ����
            // ��: [0:Hello] [1:World]

            tok = strtok(NULL, delims); // ���� ȣ��: ���ڸ� NULL�� �ָ� '���� ȣ���� ���� ��ġ'���� ��� ��ūȭ.
            // - ���� �����ڸ� ã�� '\0'�� ����, ���� ��ū�� �����͸� ��ȯ.
            // - �� �̻� ��ū�� ������ NULL ��ȯ �� while ����.
        }

        puts("");                       // �ٹٲ� ���(����). puts�� ���ڿ� �ڿ� �ڵ����� '\n'�� ���δ�.
        // �� printf���� ���� ���� �̾� �ٿ����Ƿ�, �������� ���� ������ �ܼ� �������� ���δ�.


    }

    // 2) strtok_s (MSVC Ȯ��, C11 Annex K ����) ? ������ ����
    //    ���ڿ� "context"�� �ּ� ������ ����.
#ifdef _MSC_VER
    {
        char temp[64];
        strcpy(temp, copy);

        const char* delims = " ,;";
        char* context = NULL;
        char* tok = strtok_s(temp, delims, &context);
        int idx = 0;
        printf("[strtok_s] tokens:");
        while (tok) {
            printf(" [%d:%s]", idx++, tok);
            tok = strtok_s(NULL, delims, &context);
        }
        puts("");
    }
#endif
}

//---------------------------------------------
// ���ʽ�: �޸� ��� �Լ� (memcpy/memmove/memcmp/memset)
//   - ���ڿ��� �ᱹ ����Ʈ �迭 �� �޸� ���� ������
//---------------------------------------------
void demo_memory_block(void)
{
    puts("\n[���ʽ�] �޸� ���: memcpy/memmove/memcmp/memset");

    char buf[32] = "ABCDEFGHIJ"; // 10���� + '\0'
    printf("origin: %s\n", buf);

    // 1) memcpy: ��ġ�� �ʴ� ���� ����
    memcpy(buf + 10, buf, 5); // "ABCDEFGHIJABCDE"
    buf[15] = '\0';
    printf("memcpy : %s\n", buf);

    // 2) memmove: ��ġ�� ������ ����
    //    ��: [0..9] �� [2..11]�� ��ġ�� �̵�
    char data[32] = "0123456789";
    memmove(data + 2, data, 10); // ��ħ. memmove�� ����.
    data[12] = '\0';
    printf("memmove: %s\n", data);

    // 3) memcmp: ����Ʈ ���� ��(���ڿ� ��ĢX, ���� �ݵ�� ����)
    printf("memcmp(\"ABC\",\"ABD\",3)=%d\n", memcmp("ABC", "ABD", 3));

    // 4) memset: Ư�� ������ �޸� ä���
    char z[8];
    memset(z, 0, sizeof(z)); // ���� 0(= '\0')����
    strcpy(z, "OK");
    printf("memset + strcpy: %s\n", z);
}

//---------------------------------------------
// �ǽ�: ����� �Է��� �޾� �����ϰ� �̾� ���� �� �˻�/��ūȭ
//---------------------------------------------
void practice_io_concat_search(void)
{
    puts("\n[�ǽ�] �Է� �� ���� ���̱� �� �˻�/��ūȭ");

    char name[32];
    char hobby[64];
    char sentence[128] = { 0 }; // ��� ���� ����

    input_line("�̸��� �Է�: ", name, sizeof(name));
    input_line("��̸� �Է�(��ǥ/�������� ���� ��): ", hobby, sizeof(hobby));

    // �����ϰ� �̾���̱� (���� ���� üũ)
    size_t cap = sizeof(sentence);
    size_t used = strlen(sentence);

    // "name=" ���̱�
    const char* prefix1 = "name=";
    size_t need = strlen(prefix1);
    if (used + need + 1 < cap) { strcat(sentence, prefix1); used += need; }
    if (used + strlen(name) + 1 < cap) { strcat(sentence, name); used = strlen(sentence); }

    // ", hobbies=" ���̱�
    const char* prefix2 = ", hobbies=";
    need = strlen(prefix2);
    if (used + need + 1 < cap) { strcat(sentence, prefix2); used += need; }
    if (used + strlen(hobby) + 1 < cap) { strcat(sentence, hobby); used = strlen(sentence); }

    printf("����: \"%s\"\n", sentence);

    // �˻� ����: 'a'�� ���ԵǾ� �ִ���
    if (strchr(sentence, 'a')) {
        puts("�� 'a' ���ڰ� ���ԵǾ� ����");
    }

    // �κ� ���ڿ� "name=" ��ġ
    const char* pos = strstr(sentence, "name=");
    if (pos) {
        printf("�� \"name=\" ���� �ε���: %td\n", (ptrdiff_t)(pos - sentence));
    }

    // ��� ��ūȭ(���� �ѼյǹǷ� ���纻����)
    char hobbies_copy[64];
    strcpy(hobbies_copy, hobby);
    printf("��� ��ū��:");
    for (char* t = strtok(hobbies_copy, " ,;"); t; t = strtok(NULL, " ,;")) {
        printf(" [%s]", t);
    }
    puts("");
}

//---------------------------------------------
// main: �� ���� ����
//---------------------------------------------
int main(void)
{
    puts("C <string.h> ������ ���� ���� ����");

    //demo_strlen();
    //demo_copy_concat();
    //demo_compare();
    demo_search();
    //demo_tokenize();
    //demo_memory_block();

    //practice_io_concat_search();

    puts("\n��.");
    return 0;
}