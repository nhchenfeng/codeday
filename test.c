#include <stdio.h>
#include <string.h>

int main(void)
{
	char s[] = "hello, world! welcome to china!";
	char delim[] = " ,!";

	char *token;
	for (token = strtok(s, delim); token != NULL;
	     token = strtok(NULL, delim)) {
		printf(token);
		printf("+");
	}
	printf("\n");
	return 0;
}
