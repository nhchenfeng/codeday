#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
从高到底按照身高排列，身高相同的，按照人数排列
然后从前往后插入到结果即可。因为后边的人身高高比前边低，不影响前边的结果
*/

static int **ans;

/* 快速排序的入参，与首地址相同 */
static int compare(const void *p1, const void *p2)
{
	int *data1 = *(int **)p1;
	int *data2 = *(int **)p2;

	if (data1[0] == data2[0]) {
		return data1[1] - data2[1];
	} else {
		return data2[0] - data1[0];
	}
}

void insert(int **ans, int value, int much, int total)
{
	int loop;

	if (total == 0) {
		ans[0][0] = value;
		ans[0][0] = much;
	} else {
		for (loop = total; loop > much; loop--) {
			ans[loop][0] = ans[loop - 1][0];
			ans[loop][1] = ans[loop - 1][1];
		}
	}
	ans[much][0] = value;
	ans[much][1] = much;
}

int **reconstructQueue(int **people, int peopleSize, int *peopleColSize,
		       int *returnSize, int **returnColumnSizes)
{
	int loop;
	int total;

	if (!people || !peopleSize) {
		*returnSize = 0;
		return NULL;
	}
	ans = (int **)malloc(peopleSize * sizeof(int *));
	*returnColumnSizes = (int *)malloc(peopleSize * sizeof(int));
	for (loop = 0; loop < peopleSize; loop++) {
		ans[loop] = (int *)malloc(sizeof(int) * peopleColSize[loop]);
	}
	qsort(people, peopleSize, sizeof(int *), compare);
	total = 0;
	for (loop = 0; loop < peopleSize; loop++) {
		insert(ans, people[loop][0], people[loop][1], loop);
	}
	*returnSize = peopleSize;
	for (loop = 0; loop < peopleSize; loop++) {
		(*returnColumnSizes)[loop] = 2;
	}
	return ans;
}
