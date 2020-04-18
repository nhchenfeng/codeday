#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ANS_MAX    400000
#define MAX_NODE   256

static char *ans[ANS_MAX];
static int ans_size;
static int mark[MAX_NODE];

static void add_ret(char *data)
{
	ans[ans_size] = (char *)malloc(strlen(data) + 1);
	memcpy(ans[ans_size], data, strlen(data));
	ans[ans_size][strlen(data)] = 0;
	ans_size++;
}

static void dfs(char *str, int index, int size, char *tmp)
{
	int loop;
	int cur = index;
	if (strlen(tmp) == size) {
		printf("add\n");
		add_ret(tmp);
	}
	for (loop = 0; loop < size; loop++) {
		if (!mark[str[loop]]) {
			mark[str[loop]] = 1;
			tmp[cur] = str[loop];
			dfs(str, index++, size, tmp);
			tmp[cur] = 0;
			mark[str[loop]] = 0;
		}
	}
}

char **permutation(char *S, int *returnSize)
{
	char *tmp;
	if (!S || !strlen(S)) {
		*returnSize = 0;
		return NULL;
	}
	ans_size = 0;
	tmp = malloc(strlen(S) + 1);
	memset(tmp, 0, strlen(S) + 1);
	dfs(S, 0, strlen(S), tmp);
	*returnSize = ans_size;
	return ans;
}