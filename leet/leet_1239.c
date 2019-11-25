#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int visit[100];
static char ret_str[100];
static int ans = 0;

int is_okay(char *src, char *dst)
{
	int index;
	char data[2] = { 0 };
	for (index = 0; index < strlen(src); index++) {
		data[0] = src[index];
		if (strstr(dst, data)) {
			return 0;
		}
	}
	return 1;
}

void dfs(char src[][100], char *cur, int step, int size, int tmp)
{
	int index;

        printf("dfs %s\n", cur);
	if (cur && is_okay(cur, ret_str)) {
		tmp += strlen(cur);
		memcpy(ret_str + strlen(ret_str), cur, strlen(cur));
	}
	if (step == size) {
        //printf("%s %d\n", ret_str, strlen(ret_str));
		if (strlen(ret_str) > ans)
			ans = strlen(ret_str);
		tmp = 0;
		memset(ret_str, 0, sizeof(ret_str));
	}

	for (index = step; index < size; index++) {
		if (!visit[index]) {
			visit[index] = 1;
			dfs(src, src[index], step + 1, size, tmp);
			visit[index] = 0;
		}
		memset(ret_str, 0, sizeof(ret_str));
	}
}

int maxLength(char arr[][100], int arrSize)
{
	int index;
	if (!arr || arrSize == 0)
		return 0;

	memset(visit, 0,  sizeof(visit));
	memset(ret_str, 0, sizeof(ret_str));
	ans = 0;
	dfs(arr, NULL, 0, arrSize, 0);
	return ans;
}

int main()
{
        int ret;
        char array[][100] = {
                "cha",
                "r",
                "act",
                "ers"
        };
        ret = maxLength(array, 4);
        printf("%d\n", ret);
        return 0;
}