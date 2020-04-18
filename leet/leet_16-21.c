#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
sum1 + b - a = sum2 - b + a;
b = (sum2 - sum1 + 2a) / 2
*/

static int compare(const void *p1, const void *p2)
{
	const int *data1 = (const int *)p1;
	const int *data2 = (const int *)p2;
	return *data1 - *data2;
}

int *findSwapValues(int *array1, int array1Size, int *array2, int array2Size,
		    int *returnSize)
{
	int loop;
	int sum1 = 0;
	int sum2 = 0;
	int to_find;
	int *ans;
	int *found;
	if (!array1 || !array1Size || !array2 || !array2Size) {
		*returnSize = 0;
		return NULL;
	}
	for (loop = 0; loop < array1Size; loop++) {
		sum1 += array1[loop];
	}
	for (loop = 0; loop < array2Size; loop++) {
		sum2 += array2[loop];
	}
	ans = (int *)malloc(2 * sizeof(int));
	memset(ans, 0, 2 * sizeof(int));
	qsort(array2, array2Size, sizeof(int), compare);
	for (loop = 0; loop < array1Size; loop++) {
		to_find = (sum2 - sum1 + 2 * array1[loop]) / 2;
		found = bsearch(&to_find, array2, array2Size, sizeof(int), compare);
		if (found && sum1 + *found - array1[loop] == sum2 - *found + array1[loop]) {
			*returnSize = 2;
			ans[0] = array1[loop];
			ans[1] = *found;
			return ans;
		}
	}
	*returnSize = 0;
	return ans;
}