#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

int get_size(int index_a, int a, int index_b, int b)
{
	int data1 = fmin(a, b);
	int data2 = abs(index_b - index_a);

	return data1 * data2;
}

int maxArea(int *height, int heightSize)
{
	int left = 0;
	int loop;
	int right = heightSize - 1;
	int max = 0;
	int data_left;
	int data_right;

	if (!height || heightSize < 2) {
		return 0;
	}

	while(left < right) {
		max = fmax(max, get_size(left, height[left], right, height[right]));
		data_left = height[left];
		data_right = height[right];
		if (data_left < data_right) {
			while(left < right) {
				if (height[left] > data_left) {
					break;
				}
				left++;
			}
		} else {
			while(left < right) {
				if (height[right] > data_right) {
					break;
				}
				right--;
			}
		}
		max = fmax(max, get_size(left, height[left], right, height[right]));
	}
	return max;
}