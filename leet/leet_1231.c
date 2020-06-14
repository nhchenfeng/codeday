#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>

/*
二分查找，返回左边界
*/

static int size;
static int total;

int avilable(int *data, int key)
{
	int loop;
	int tsum = 0;
	int tcount = 0;

	for (loop = 0; loop < size; loop++) {
		tsum += data[loop];
		if (tsum < key) {
			continue;
		} else {
			tsum = 0;
			tcount++;
			if (tcount > total)
				return 1;
		}
	}
	tcount--;
	if (tcount >= total) {
		return 1;
	}
	return 0;
}

int binary_search(int *data, int left, int right)
{
	int mid = (right - left) / 2 + left;

	if (right - left == 1) {
		if (avilable(data, right)) {
			return right;
		}
		if (avilable(data, left)) {
			return left;
		}
		return mid;
	}

	if (avilable(data, mid)) {
		left = mid;
	} else {
		right = mid;
	}
	return binary_search(data, left, right);
}

int maximizeSweetness(int *sweetness, int sweetnessSize, int K)
{
	if (!sweetness || !sweetnessSize) {
		return 0;
	}
	size = sweetnessSize;
	total = K;
	return binary_search(sweetness, 0, INT_MAX);
}
