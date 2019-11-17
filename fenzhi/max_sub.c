#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_SIZE(a)  (sizeof(a) / sizeof((a)[0]))
#define MAX(a, b)      ((a) > (b) ? (a) : (b))

int divide(int *data, int left, int right)  /* [left, right] */
{
	int loop;
	int ret_left;
	int ret_right;
	int ret_mid;
	int ret;
	int s1 = 0;
	int s2 = 0;
	int tmp_s1 = 0;
	int tmp_s2 = 0;
	int mid = (left + right) / 2;
	if (left == right) {
		if (data[left] < 0)
			return 0;
		return data[left];
	}
	ret_left = divide(data, left, mid);
	ret_right = divide(data, mid + 1, right);

	for(loop = mid; loop >= left; loop--) {
		tmp_s1 = tmp_s1 + data[loop];
		s1 = MAX(s1, tmp_s1);
	}
	for(loop = mid + 1; loop <= right; loop++) {
		tmp_s2 = tmp_s2 + data[loop];
		s2 = MAX(s2, tmp_s2);
	}
	ret_mid = s1 + s2;
	printf("mid %d = %d + %d\n", ret_mid, s1, s2);

	printf("[%d - %d] left %d right %d mid %d\n", left, right, ret_left, ret_right, ret_mid);
	ret = MAX(ret_left, ret_right);
	ret = MAX(ret, ret_mid);
	return ret;
}

int max_sub(int *nums, int size)
{
	int ret;
	ret = divide(nums, 0, size - 1);
	printf("ret %d\n", ret);
	return ret;
}

int main()
{
	int ret;
	int local_data[] = {2,4,-7,5,2,-1,2,-4,3};
	ret = max_sub(local_data, ARRAY_SIZE(local_data));
	return 0;
}