#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * dp_ret[i, j] 表示 i 到 j 的最大硬币数
 * dp_ret[i, j] = max(dp_ret[i][k - 1] + dp_ret[k + 1][j] + nums[k - 1] * nums[k] * nums[k + 1]) (i <= k << j)
 */

#ifdef debug
#define info printf
#else
#define info
#endif

static int dp_ret[501][501];
static int *da;
static int da_size;

#define max(x, y) ((x) < (y) ? (y) : (x))

int data(int i)
{
	if (i == -1)
		return 1;

	if (i == da_size)
		return 1;

	if (i < -1 || i > da_size)
		info("error\n");

	return da[i];
}

int dp_func(int i, int j)
{
	int k, left, right, last;
	info("into %d %d\n", i, j);
	if (i > j) {
		info("dp[%d][%d] %d\n", i, j, 0);
		return 0;
	}
	if (dp_ret[i][j]) {
		info("dp[%d][%d] %d\n", i, j, dp_ret[i][j]);
		return dp_ret[i][j];
	}

	for (k = i; k <= j; k++) {
		left = dp_func(i, k - 1);
		right = dp_func(k + 1, j);
		last = data(k) * data(i - 1) * data(j + 1);
		dp_ret[i][j] = max(dp_ret[i][j], left + last + right);
	}
	info("dp[%d][%d] %d\n", i, j, dp_ret[i][j]);
	return dp_ret[i][j];
}

int maxCoins(int* nums, int numsSize)
{
	memset(dp_ret, 0, sizeof(dp_ret));
	if (!nums || numsSize == 0)
		return 0;
	if (numsSize == 1)
		return nums[0];

	da = nums;
	da_size = numsSize;
	dp_func(0, numsSize - 1);
	return dp_ret[0][numsSize - 1];
}

int main()
{
	int test[] = {3,4,6,3,7,0,7,5,1,5,2,5,9,6,4,8,4,3,6,6,6,7,4,9,2,6,8,4,0,0,2,7,8,0,4,7,4,1};
	int ret = maxCoins(test, sizeof(test) / sizeof(test[0]));

	printf("ret %d\n", ret);
	return 0;
}
