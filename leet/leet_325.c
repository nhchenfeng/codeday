#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
前缀和pre_sum[x]
sum[i ~ j]区间和 等于pre_sum[j] - pre_sum[i - 1]
*/

#define MAX(a, b)  ((a) > (b) ? (a) : (b))
#define MAX_NODE   1024 * 1024
static int pre_sum[MAX_NODE];

int maxSubArrayLen(int* nums, int numsSize, int k)
{
	int loop;
	int i;
	int j;
	int sum = 0;
	int ret_max = 0;
	if (!nums || numsSize == 0) {
		return 0;
	}
	pre_sum[0] = 0;
	for (i = 0; i < numsSize; i++) {
		sum += nums[i];
		pre_sum[i + 1] = sum;
		for (j = i; j >= 0; j--) {
			if (pre_sum[i + 1] - pre_sum[j] == k) {
				ret_max = MAX(ret_max, i + 1 - j);
			}
		}
	}
	return ret_max;
}