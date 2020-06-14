#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *runningSum(int *nums, int numsSize, int *returnSize)
{
	int loop;
	int *ans;
	long long tmp = 0;

	if (!nums || !numsSize) {
		*returnSize = 0;
		return NULL;
	}
	ans = (int *)malloc(numsSize * sizeof(int));

	for (loop = 0; loop < numsSize; loop++) {
		tmp += nums[loop];
		ans[loop] = tmp;
	}
	*returnSize = numsSize;
	return ans;
}