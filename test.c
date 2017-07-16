#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	char *a = "123";
	char *b = "234";
	char c[1024] = {0};
	sprintf(c, "%s%s", a, b);
	printf("%s\n", c);
}
