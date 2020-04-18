#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
	char *str;
	int len;
	char first[100];
	char last[100];
};

static char **ans;
static int ans_size;
static struct node array[100];

void split_to_node(struct node *data, char *str)
{
	char *tmp = strdup(str);
	char *index;
	int first = 0;

	data->str = str;
	data->len = strlen(str);
	printf("source %s\n", str);
	for (index = strsep(&tmp, " "); index != NULL;
	     index = strsep(&tmp, " ")) {
		if (!first) {
			memcpy(data->first, index, strlen(index));
			data->first[strlen(index)] = 0;
			first = 1;
		}
		memcpy(data->last, index, strlen(index));
		data->last[strlen(index)] = 0;
	}
}

int is_okay(struct node *src, struct node *dst)
{
	printf("compare %s with %s first\n", src->str, dst->str);
	if (!strcmp(src->last, dst->first)) {
		printf("okay %s with %s first\n", src->str, dst->str);
		return 1;
	}
	return 0;
}

void add_ret(struct node *src, struct node *dst)
{
	int loop;

	char tmp[200] = { 0 };
	printf("add ret %s %s\n", src->str, dst->str);
	memcpy(tmp, src->str, src->len - strlen(src->last));
	strcat(tmp, dst->str);
	for (loop = 0; loop < ans_size; loop++) {
		if (!strcmp(tmp, ans[loop]))
			return;
	}
	printf("add tmp %s\n", tmp);
	memcpy(ans[ans_size++], tmp, strlen(tmp));
}

static int compare(const void *p1, const void *p2)
{
	char *data1 = *(const char **)p1;
	char *data2 = *(const char **)p2;

	return strcmp(data1, data2);
}

char **beforeAndAfterPuzzles(char **phrases, int phrasesSize, int *returnSize)
{
	int loop;
	int next;

	if (!phrases || !phrasesSize) {
		*returnSize = 0;
		return NULL;
	}
	ans_size = 0;
	ans = (char **)malloc(100 * sizeof(char *));
	memset(array, 0, sizeof(array));
	for (loop = 0; loop < 100; loop++) {
		ans[loop] = (char *)malloc(200);
		memset(ans[loop], 0, 200);
	}
	for (loop = 0; loop < phrasesSize; loop++) {
		split_to_node(&array[loop], phrases[loop]);
	}
	for (loop = 0; loop < phrasesSize; loop++) {
		for (next = 0; next < phrasesSize; next++) {
			if (loop == next)
				continue;
			if (is_okay(&array[loop], &array[next])) {
				add_ret(&array[loop], &array[next]);
			}
		}
	}
	*returnSize = ans_size;
	qsort(ans, ans_size, sizeof(char *), compare);
	return ans;
}
