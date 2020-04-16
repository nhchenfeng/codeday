#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MAX_NODE 256
#define MAX_STR 1024

static int hash[MAX_NODE];
static int ans;
static char result[MAX_STR];

int is_okay(char *str)
{
	int loop;
	int next;
	int len = strlen(str);
	int flag = 0;

	for (loop = 0; loop < len; loop++) {
		hash[str[loop]]++;
		if (hash[str[loop]] > 1) {
			flag = 1;
		}
	}
	for (loop = 0; loop < len; loop++) {
		hash[str[loop]]--;
	}
	if (flag)
		return 0;
	return 1;
}

void dfs(char **str, int index, int size)
{
	int loop;
	int next;
	int len = strlen(result);
	int str_len;

	for (next = index; next < size; next++) {
		if (is_okay(str[next])) {
			str_len = strlen(str[next]);
			memcpy(result + strlen(result), str[next],
			       strlen(str[next]));
			for (loop = 0; loop < str_len; loop++) {
				hash[str[next][loop]]++;
			}
			ans = MAX(ans, strlen(result));
			dfs(str, next, size);
			for (loop = 0; loop < str_len; loop++) {
				hash[str[next][loop]]--;
			}
			for (loop = len; loop < str_len; loop++) {
				result[loop] = 0;
			}
		}
	}
}

int maxLength(char **arr, int arrSize)
{
	if (!arr || !arrSize) {
		return 0;
	}
	ans = 0;
	memset(hash, 0, sizeof(hash));
	memset(result, 0, sizeof(result));
	dfs(arr, 0, arrSize);
	return ans;
}
