#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
单调队列，递减只留大的，每次元素进来把优先级比自己低的赶走(数值小的出队)，只留下大的
队首与当前的游标大于K时，队首出队
*/

int *maxSlidingWindow(int *nums, int numsSize, int k, int *returnSize)
{
	int loop;
	int *list;
	int *ans;
	int left = 0;
	int right = 0;
	int ans_size = 0;
	if (!nums || !numsSize) {
		*returnSize = 0;
		return NULL;
	}
	list = (int *)malloc(numsSize * sizeof(int));
	ans = (int *)malloc(numsSize * sizeof(int));

	for (loop = 0; loop < numsSize; loop++) {
		while(left < right && nums[list[right - 1]] <= nums[loop]) /* 这里写法较为巧妙，第一个天然入队 */
			right--;

		list[right++] = loop; /* 每次存放index */
		if (loop - list[left] >= k) { /* 队首太老，压出，注意比较index */
			left++;
		}
		if (loop >= k - 1) {
			ans[ans_size++] = nums[list[left]];
		}
	}
	*returnSize = ans_size;
	return ans;
}