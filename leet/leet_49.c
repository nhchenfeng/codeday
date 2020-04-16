#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int compare(const void *p1, const void *p2)
{
	const char *data1 = (const char *)p1;
	const char *data2 = (const char *)p2;
	return *data1 - *data2;
}

int same(char *src, char *dst)
{
	char data1[100] = {0};
	char data2[100] = {0};
	if (strlen(src) != strlen(dst))
		return 0;
	strcpy(data1, src);
	strcpy(data2, dst);
	qsort(data1, strlen(src), sizeof(char), compare);
	qsort(data2, strlen(dst), sizeof(char), compare);
	return !strcmp(src, dst);
}

void init(int n, int *father)
{
        int i;

        for (i = 0; i < n; i++) {
                father[i] = i;
        }
}

int find(int x, int *father)
{
        if (x != father[x]) {
                father[x] = find(father[x], father);
        }

        return father[x];
}

void union_circle(int x, int y, int *father)
{
        int fx = find(x, father);
        int fy = find(y, father);

        if (fx != fy) {
                father[fx]= fy;
        }
}

static char ***ans;
static int ans_size;
static int *hash;
static int *col;

static void init_ans(int size)
{
	int loop;
	int next;

	ans_size = 0;
	ans = (char ***)malloc(size * sizeof(char **));
	col = (int *)malloc(size * sizeof(int));
	memset(col, 0, size * sizeof(int));
	for (loop = 0; loop < size; loop++) {
		ans[loop] = (char **)malloc(size * sizeof(char *));
		for (next = 0; next < size; next++) {
			ans[loop][next] = (char *)malloc(100);
			memset(ans[loop][next], 0, 100);
		}
	}
}

char ***groupAnagrams(char **strs, int strsSize, int *returnSize,
		      int **returnColumnSizes)
{
	int loop;
	int next;
	int tmp;
	int *father;

	if (!strs || !strsSize || strsSize > 100) {
		*returnSize = 0;
		return NULL;
	}

	father = (int *)malloc(strsSize * sizeof(int));
	hash = (int *)malloc(strsSize * sizeof(int));
	init_ans(strsSize);
	init(strsSize, father);
	for (loop = 0; loop < strsSize; loop++) {
		for (next = loop + 1; next < strsSize; next++) {
			tmp = same(strs[loop], strs[next]);
			if (tmp) {
				union_circle(next, loop, father);
			}
		}
	}
	for (loop = 0; loop < strsSize; loop++) {
		tmp = find(loop, father);
		//printf("loop %d fater %d\n", loop, tmp);
		if (tmp == loop) {
			printf("%s new line %d col %d\n", strs[loop], ans_size, col[ans_size]);
			hash[loop] = ans_size;
			strcpy(ans[ans_size][col[ans_size]], strs[loop]);
			col[ans_size]++;
			ans_size++;
		} else {
			printf("%s into line %d col %d\n", strs[loop], col[hash[tmp]], col[hash[tmp]]);
			strcpy(ans[hash[tmp]][col[hash[tmp]]], strs[loop]);
			col[hash[tmp]]++;
		}
	}
	printf("end ans size %d\n", ans_size);
	*returnSize = ans_size;
	*returnColumnSizes = col;
	return ans;
}