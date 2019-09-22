/*
 * 最长递增子序列：longest increasing subsequence
 * 设序列L = {a1, a2, a3, ..., an} 是n个不同的整数序列，序列L中的最长
 * 递增子序列为LIS = {ak1, ak2, ..., akm}, 其中ak1 < ak2 < ... < akm.
 * 求akm
 * 例如n = 5
 * 有序列 5 1 4 2 3
 * 则最长递增子序列为1 2 3, m = 3
 */
/*
 * 分别求以a1, a2, a3, ..., an为末尾的最长递增子序列放到数组b中。
 * 然后求b中的最大长度
 * 以a[k]为结尾的最长递增子序列：
 * 1. 找到a[j] (j < k && a[j] < a[k]) 则b[k] = max(a[j]) + 1,可能找到多个a[j]
 * 2. 找不到a[j] 满足j < k && a[j] < a[k], 则b[k] = 1;
 */

/*
 *
 * f(n) =
 * if (n = 0)
 * 	= 1
 * if (a(0 ... n -1) < a[n])
 * 	= max(f(0 .... n - 1)) + 1
 * else
 * 	= 1
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int lcs(int *arrary, int total, int n, int *b)
{
	int longest = 1;
	int i;
	int max = 1;
	/*printf("get lcs %d\n", n);*/
	if (n == 0) {
		/*printf("n == 0 return 1");*/
		if (b[0] == 0)
			b[0] = 1;
		return 1;
	}
	/*if (b[i]) {*/
		/*printf("[%d] just return from b %d\n", i, b[i]);*/
		/*return b[i];*/
	/*}*/

	for (i = 0; i < n; i++) {
		if (arrary[i] < arrary[n]) {
			/*printf("to get %d going to lcs %d\n", n, i);*/
			if (b[i])
				longest = b[i] + 1;
			else
				longest = lcs(arrary, total, i, b) + 1;
			/*printf("[%d] lcs %d\n", i, longest);*/
			if (longest > max) {
				max = longest;
			}
		}
	}
	/*printf("no little than return 1\n");*/
	if (b[i] == 0) {
		printf("set [%d] %d\n", i, max);
		b[i] = max;
	}
	return max;
}

int main(void)
{
	int i;
	int tmp;
	int max = 0;
	int a[] = {1, 2, 4, 3, 8, 9, 7, 10, 5, 6};
	int *b = (int *)malloc(10 * sizeof(int));
	memset(b, 0, 10 * sizeof(int));
	for (i = 0; i < 10; i++) {
		tmp = lcs(a, 10, i, b);
		if(tmp > max)
			max = tmp;
	}
	printf("max %d\n", max);
}
