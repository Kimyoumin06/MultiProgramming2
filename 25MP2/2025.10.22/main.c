#include <stdio.h>
#include <conio.h>

struct Fish
{
	char *name;
	char *talk;
};

int main()
{
	struct Fish fish1;
	fish1.name = "Name";

	printf("%s\n", fish1.name);
	return 0;
}