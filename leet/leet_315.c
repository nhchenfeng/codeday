#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

/*
归并排序，在merge的时候，左右相比较
右边比左边大的数量天然知道，为了方便，这里可以逆序排列
*/

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

int *ans_array;

void merge_sort(int *data, int left, int right, int *tmp, int *sort)
{
	int mid;
	int left_index;
	int right_index;
	int loop;
	int tmp_left;
	int tmp_right;
	if (left == right) {
		return;
	}
	mid = left + (right - left) / 2;
	merge_sort(data, left, mid, tmp, sort);
	merge_sort(data, mid + 1, right, tmp, sort);
	left_index = left;
	right_index = mid + 1;
	for (loop = left; loop <= right; loop++) {
		if (left_index <= mid) {
			tmp_left = data[sort[left_index]]; 
		} else{
			tmp_left = INT_MAX;
		}
		if (right_index <= right) {
			tmp_right = data[sort[right_index]]; 
		} else{
			tmp_right = INT_MAX;
		}
		if (tmp_right < tmp_left) {
			tmp[loop] = sort[right_index];
			ans_array[sort[left_index]]++;
			right_index++;
		} else {
			tmp[loop] = sort[left_index];
			left_index++;
		}
	}
	for (loop = left; loop <= right; loop++) {
		sort[loop] = tmp[loop];
	}
}

int *countSmaller(int *nums, int numsSize, int *returnSize)
{
	int loop;
	int *tmp;
	int *sort;
	if (!nums || numsSize == 0) {
		*returnSize = 0;
		return NULL;
	}
	ans_array = (int *)malloc(numsSize * sizeof(int));
	memset(ans_array, 0, sizeof(ans_array));
	tmp = (int *)malloc(numsSize * sizeof(int));
	sort = (int *)malloc(numsSize * sizeof(sort));
	for (loop = 0; loop < numsSize; loop++) {
		sort[loop] = loop;
	}
	merge_sort(nums, 0, numsSize - 1, tmp, sort);
	*returnSize = numsSize;
	return ans_array;
}

int main()
{
	int loop;
	int *ret;
	int ret_size;
	int data[] = { 5, 2, 6, 1 };
	ret = countSmaller(data, ARRAY_SIZE(data), &ret_size);
	for (loop = 0; loop < ret_size; loop++) {
		//printf("%d\n", data[loop]);
		printf("%d\n", ret[loop]);
	}
}