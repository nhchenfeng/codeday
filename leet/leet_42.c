#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(a, b)         ((a) < (b) ? (a) : (b))
#define MAX(a, b)         ((a) > (b) ? (a) : (b))
#define ARRAY_SIZE(x)     (sizeof(x) / sizeof((x)[0])) 

int get_max(int *data, int left, int right, int *new_left)
{
	int i;
	int index;
	int tmp = 0;
	for (i = left; i <= right; i++) {
		if (data[i] >= tmp) {
			tmp = data[i];
			*new_left = i;
		}
	}
	//printf("get [%d %d] return %d new left %d\n", left, right, tmp, *new_left);
	return tmp;
}

int update(int *height, int left, int right, int base)
{
	int tmp = 0;
	int i;
	for (i = left; i < right; i++) {
		if (height[i] < base) {
			tmp += base - height[i];
			height[i] = base;
		}
	}
	return tmp;
}

int trap(int* height, int heightSize)
{
	int left;
	int right;
	int new_left = 0;
	int index;
	int max;
	int min;
	int sum = 0;
	left = 0;
	if (!height || heightSize <= 2) {
		return 0;
	}
	max = height[0];
	min = height[0];
	for (right = left + 2; right < heightSize; right++){
		max = get_max(height, left, right - 1, &left);
		min = MIN(max, height[right]);
		sum += update(height, left, right, min);
		//left = new_left;
	}
	return sum;
}

int main()
{
	int ret;
	int data[] = {5,5,4,7,8,2,6,9,4,5};
	ret = trap(data, ARRAY_SIZE(data));
	printf("ret %d\n", ret);
	return 0;
}