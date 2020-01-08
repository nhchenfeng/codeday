#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	int data;
	char *number = "345";
	int ret = snprintf(&data, 3, "%d", number);
	printf("ret %d data %d\n", ret, data);
}
