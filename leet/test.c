#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>

void split(char *src)
{
	char *tmp = strdup(src);
	char *index;

	printf("source %s\n", src);
	for (index = strsep(&tmp, " "); index != NULL;
	     index = strsep(&tmp, " ")) {
		printf("%s position %d\n", index, index - tmp);
	}
	free(tmp);
}

int main()
{
	int data[10];
	int data2[100];
	split("hello world 123");
	split("hello");
	memcpy(data, data2, 0);
}