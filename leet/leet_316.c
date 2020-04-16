#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
单调递增队列：
第loop个入队的时候，往前反压，将所有的大于当前loop值的且不是最后一个的压出
loop入队的时候，如果前边已经有了则直接跳过，反之入队
*/

#define MAX_NODE 256

static char *list;
static int last[MAX_NODE];
static int used[MAX_NODE];

char *removeDuplicateLetters(char *s)
{
	int len;
	int loop;
	int next;
	int left = 0;
	int right = 0;

	if (!s)
		return NULL;
	len = strlen(s);
	list = (char *)malloc(len);
	for (loop = 0; loop < len; loop++) {
		last[s[loop]] = loop;
	}
	memset(used, 0, sizeof(used));
	list[right++] = s[0];
	used[s[0]] = 1;

	for (loop = 1; loop < len; loop++) {
		if (used[s[loop]]) {
			printf("%c used\n", s[loop]);
			continue;
		}
		printf("right %d loop %c\n", right, s[loop]);
		for (next = right - 1; next >= 0; next--) {
			if (list[next] > s[loop] && last[list[next]] >= loop) {
				printf("next %d last %d %c loop %c loop %d\n",
				       next, last[s[next]], s[next], s[loop],
				       loop);
				used[list[next]]--;
				right--;
			} else {
				break;
			}
		}
		used[s[loop]] = 1;
		printf("[%d] set %c\n", right, s[loop]);
		list[right++] = s[loop];
	}
	list[right] = 0;
	return list;
}

int main()
{
	char *ret = removeDuplicateLetters("ab");
	printf("%s\n", ret);
	return 0;
}