#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NODE    1000
#define MAX_LEN     100
static char **ret_array;
static int ret_size;
static char *data;

static int inited;

void init_local()
{
	int loop;
	if (!inited) {
		ret_array = (char *)malloc(MAX_NODE * sizeof(char *));
		for (loop = 0; loop < MAX_NODE; loop++) {
			ret_array[loop] = malloc(sizeof(char) * MAX_LEN);
		}
	}
	for (loop = 0; loop < MAX_NODE; loop++) {
		memset(ret_array[loop], 0, sizeof(char) * MAX_LEN);
	}
}

void dfs(char *data, int index, int total, int step)
{
	dfs(data, index + 1, )
}

char **addOperators(char *num, int target, int *returnSize)
{
	if (!num)
		return NULL;

	init_local();
	data = num;
	dfs(num, 0, strlen(num), 0);
}

int main()
{
	return 0;
}