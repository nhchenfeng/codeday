#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_NODE 256
#define MAX_LIST 4096

static char map[MAX_NODE][MAX_NODE];
static int list[MAX_LIST];
static int left;
static int right;
static char ans[MAX_NODE];
static int ans_size;
static int order[MAX_NODE];
static int weight[MAX_NODE];

static void init_local()
{
	left = 0;
	right = 0;
	memset(ans, 0, sizeof(ans));
	memset(map, 0, sizeof(map));
	memset(order, -1, sizeof(order));
}

static int local_compare(char *src, char *dst)
{
	int loop;

	int size1 = strlen(src);
	int size2 = strlen(dst);
	int size = fmin(size1, size2);
	printf("compare %s %s ans %s\n", src, dst, ans);
	for (loop = 0; loop < size; loop++) {
		printf("dst %c weight %d\n", dst[loop], weight[dst[loop]]);
		printf("src %c weight %d\n", src[loop], weight[src[loop]]);
		if (weight[dst[loop]] > weight[src[loop]])
			return 1;
	}
	if (size2 >= size1) {
		return 1;
	}
	return -1;
}

char *alienOrder(char **words, int wordsSize)
{
	int loop;
	int next;
	int size;
	int pre;
	int cur;
	int tmp = 0;
	int ret;

	init_local();
	if (!words || !wordsSize)
		return ans;

	for (loop = 0; loop < wordsSize; loop++) {
		size = strlen(words[loop]);
		for (next = 0; next < size; next++) {
			if (order[words[loop][next]] == -1) {
				order[words[loop][next]] = 0;
			}
		}
	}
	for (loop = 0; loop < wordsSize; loop++) {
		size = strlen(words[loop]);
		for (next = 0; next < size - 1; next++) {
			if (!map[words[loop][next]][words[loop][next + 1]] &&
			    words[loop][next] != words[loop][next + 1]) {
				order[words[loop][next + 1]]++;
				map[words[loop][next]][words[loop][next + 1]] =
					1;
			}
		}
	}
	for (loop = 'a'; loop <= 'z'; loop++) {
		if (!order[loop]) {
			list[right++] = loop;
		}
	}
	while (left < right) {
		size = right - left;
		tmp++;
		for (next = 0; next < size; next++) {
			pre = list[left++];
			weight[pre] = tmp;
			ans[ans_size++] = pre;
			for (loop = 'a'; loop <= 'z'; loop++) {
				if (map[pre][loop]) {
					printf("pre %d next %d\n", pre, loop);
					order[loop]--;
					if (!order[loop]) {
						list[right++] = loop;
					}
				}
			}
		}
	}
	for (loop = 0; loop < wordsSize - 1; loop++) {
		ret = local_compare(words[loop], words[loop + 1]);
		if (ret < 0) {
			ans[0] = 0;
			return ans;
		}
	}
	return ans;
}
