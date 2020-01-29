#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_SIZE(x)    ((sizeof(x) / sizeof(x)[0]))

int binary_search_index(int *data, int left, int right)
{
	int mid = (left + right) / 2;
	if (right - left == 1) {
		if (data[right] < data[left])
			return left;
		else {
			printf("error\n");
			return -1;
		}
	}

	if (data[left] < data[mid] && data[right] < data[mid]) {
		return binary_search_index(data, mid, right);
	} else if (data[left] > data[mid] && data[right] > data[mid]) {
		return binary_search_index(data, left, mid);
	} else {
		printf("error\n");
		return -1;
	}
}

int binary_search(int *data, int left, int right, int key)
{
	int mid = (left + right) / 2;
	if (left == right) {
		if (data[left] == key)
			return left;
		else
			return -1;
	}
	if (right - left == 1) {
		if (data[left] == key)
			return left;
		else if (data[right] == key)
			return right;
		else
			return -1;
	}
	if (data[mid] > key)
		return binary_search(data, left, mid, key);
	else
		return binary_search(data, mid, right, key);
}

int search(int *nums, int numsSize, int target)
{
	int ret;

	int tag;
	if (!nums || numsSize == 0)
		return -1;
	if (numsSize == 1) {
		if (nums[0] == target)
			return 0;
		else
			return -1;
	}
	tag = binary_search_index(nums, 0, numsSize - 1);
	if (tag == -1) {
		return binary_search(nums, 0, numsSize - 1, target);
	}
	ret = binary_search(nums, 0, tag, target);
	if (ret != -1)
		return ret;
	ret = binary_search(nums, tag + 1, numsSize - 1, target);
	return ret;	
}

int main()
{
	int data[] = {1};
	int tag = binary_search(data, 0, ARRAY_SIZE(data) - 1, 1);
	printf("tag %d\n", tag);
}